#include "TrackingMaterial.hh"

using namespace CLHEP;

TrackingMaterial::TrackingMaterial(G4String name) :
  PPS::GeometryComponent(name),
  fSD(0), fThickness(300.*um)
{
  fMessenger = new TrackingMaterialMessenger(this);
}

TrackingMaterial::~TrackingMaterial()
{
  delete fMessenger;
}

G4VPhysicalVolume*
TrackingMaterial::BuildOneStation()
{
  G4cout << __PRETTY_FUNCTION__ << G4endl;
  
  /*G4Box* container_box = new G4Box("Container", 10.*cm/2., 10.*cm/2., fThickness/2.);
  G4LogicalVolume* container_log = new G4LogicalVolume(container_box, fMaterial->Silicon, GetLogName(), 0, 0, 0);
  G4PVPlacement* container_phys = new G4PVPlacement(
    &fRotation,
    G4ThreeVector(
      fPosition.x(),
      fPosition.y(),
      fPosition.z()-fThickness/2.
    ),
    container_log,
    GetPhysName(),
    fParentLog,
    false,
    0, true
  );*/
  
  G4cout << "log container name=" << fParentLog->GetName() << G4endl;
  
  G4Box* container_box = new G4Box("Container", 10.*cm/2., 10.*cm/2., fThickness/2.);
  G4LogicalVolume* container_log = new G4LogicalVolume(container_box, fContainerMaterial, GetLogName(), 0, 0, 0);
  G4PVPlacement* container_phys = new G4PVPlacement(
    &fRotation,
    G4ThreeVector(
      fPosition.x(),
      fPosition.y(),
      fPosition.z()-fThickness/2.
    ),
    container_log,
    GetPhysName(),
    fParentLog,
    false,
    0
  );
 G4cout << "physical container built" << G4endl;
  
  G4Box* sensor_box = new G4Box("sensor", 10.*cm/2., 10.*cm/2., fThickness/2.);
  G4LogicalVolume* sensor_log = new G4LogicalVolume(
    sensor_box,
    fMaterial->Silicon,
    "sensor_log",
    0, 0, 0);
  new G4PVPlacement(
    &fRotation,
    G4ThreeVector(),
    sensor_log,
    "sensor_phys",
    container_log,
    false,
    0
  );

  return container_phys;
}

void
TrackingMaterial::BeforeConstruct()
{
  //fSD = new TrackingMaterialSD(fSDname);
  //G4SDManager::GetSDMpointer()->AddNewDetector(fSD);
  
  fPhys = BuildOneStation();
}

REGISTER_COMPONENT(TrackingMaterial, "TRACKINGMATERIAL")

////////////////////////////////////////////////////////////////////////

TrackingMaterialMessenger::TrackingMaterialMessenger(TrackingMaterial* tm) :
  fTM(tm)
{
  std::ostringstream dir; dir << "/TM/" << tm->GetName() << "/";
  fTMDir = new G4UIdirectory(dir.str().c_str());
  fTMDir->SetGuidance("UI commands for the PPS-TrackingMaterial");
  
  std::ostringstream cmd; cmd << dir.str() << "setThickness";
  fThickness = new G4UIcmdWithADoubleAndUnit(cmd.str().c_str(), this);
  fThickness->SetDefaultUnit("um");
  fThickness->SetParameterName("tracking_thickness", true);
  fThickness->AvailableForStates(G4State_PreInit, G4State_Idle);
}

TrackingMaterialMessenger::~TrackingMaterialMessenger()
{
  delete fTMDir;
  delete fThickness;
}

void
TrackingMaterialMessenger::SetNewValue(G4UIcommand* command, G4String value)
{ 
  if (command==fThickness) {
    fTM->SetThickness(fThickness->GetNewDoubleValue(value));
  }
}

////////////////////////////////////////////////////////////////////////

TrackingMaterialSD::TrackingMaterialSD(G4String name) :
  PPS::SensitiveDetector<EnvironmentalEvent>(name)
{
  RegisterEvent();
}

TrackingMaterialSD::~TrackingMaterialSD()
{}

G4bool
TrackingMaterialSD::ProcessHits(G4Step* step, G4TouchableHistory*)
//TrackingMaterialSD::Hit(G4Step* step)
{
  G4Track* track = step->GetTrack();
  G4ThreeVector mom = track->GetMomentum();
  G4ThreeVector pos = track->GetVertexPosition();
  EnvironmentalHit hit;
  hit.SetMomentum(TLorentzVector(mom.x(), mom.y(), mom.z(), track->GetTotalEnergy()));
  hit.SetPosition(TLorentzVector(pos.x(), pos.y(), pos.z(), track->GetGlobalTime()));
  fEvent->AddSecondaryHit(hit);
  //PPS::TrackInformation* ti = static_cast<PPS::TrackInformation*>(track->GetUserInformation());

  //QuartLPhotonHit* hit = new QuartLPhotonHit;
  //hit->SetIncomingParticle(fRunAction->GetRunInformation()->GetIncomingParticle(ti->GetOriginalTrackID()-1));
  //hit->SetCellID(step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo());

  // One kills the particle after its arrival in the sensitive detector
  // track->SetTrackStatus(fStopAndKill);

  return true;

}
