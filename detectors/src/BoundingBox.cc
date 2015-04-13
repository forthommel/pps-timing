#include "BoundingBox.hh"

using namespace CLHEP;

BoundingBox::BoundingBox(G4String name) :
  PPS::GeometryComponent(name),
  fSD(0), fBuilt(false)
{}

void
BoundingBox::BeforeConstruct()
{ 
  //G4VSensitiveDetector* theSD = G4SDManager::GetSDMpointer()->FindSensitiveDetector(fSDname, false);
  //if (theSD) theSD->clear();

  G4cout << __PRETTY_FUNCTION__ << " -> building the SD for the bounding box" << G4endl;
  fSD = new BoundingBoxSD(fSDname);
  //G4SDManager::GetSDMpointer()->AddNewDetector(fSD); 
  
  if (fBuilt) return;

  G4Box* container_box = new G4Box("BoundingBox", 2.*m/2., 2.*m/2., 2.*m/2.);
  fLog = new G4LogicalVolume(container_box, fContainerMaterial, GetLogName(), 0, 0, 0);
  fPhys = new G4PVPlacement(&fRotation, G4ThreeVector(fPosition.x(), fPosition.y(), fPosition.z()),
    fLog,
    fSDname,
    0, false, 0, true);
  fPhys->GetLogicalVolume()->SetSensitiveDetector(fSD);
  
  fBuilt = true;
}

REGISTER_COMPONENT(BoundingBox, "BOUNDINGBOX")

////////////////////////////////////////////////////////////////////////

BoundingBoxSD::BoundingBoxSD(G4String name) :
  PPS::SensitiveDetector<EnvironmentalEvent>(name)
{
  RegisterEvent();
}

BoundingBoxSD::~BoundingBoxSD()
{}

G4bool
BoundingBoxSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  fEventTime = step->GetPreStepPoint()->GetGlobalTime();
  G4Track* track = step->GetTrack();
  
  PPS::TrackInformation* ti = static_cast<PPS::TrackInformation*>(track->GetUserInformation());
  if (ti->GetOriginalTrackID()==0) return false;
  
  G4ThreeVector mom = track->GetMomentum();
  G4ThreeVector vtx = track->GetVertexPosition();
  G4ThreeVector pos = step->GetPostStepPoint()->GetPosition();
  
  EnvironmentalHit hit;
  hit.SetMomentum(TLorentzVector(mom.x()/GeV, mom.y()/GeV, mom.z()/GeV, track->GetTotalEnergy()/GeV));
  hit.SetVertexPosition(TLorentzVector(vtx.x()/m, vtx.y()/m, vtx.z()/m, track->GetGlobalTime()/second));
  hit.SetPosition(TLorentzVector(pos.x()/m, pos.y()/m, pos.z()/m, step->GetPostStepPoint()->GetGlobalTime()/second));
  hit.SetPDGId(track->GetDefinition()->GetPDGEncoding());
  fEvent->AddSecondaryHit(hit);

  //QuartLPhotonHit* hit = new QuartLPhotonHit;
  //fEvent->SetIncomingParticle(fRunAction->GetRunInformation()->GetIncomingParticle(ti->GetOriginalTrackID()-1));
  //hit->SetCellID(step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo());
  //fEvent->AddHit(hit);

  // One kills the particle after its arrival in the sensitive detector
  //track->SetTrackStatus(fStopAndKill);

  return true;

}
