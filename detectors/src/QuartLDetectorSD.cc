#include "QuartLDetectorSD.hh"

using namespace CLHEP;

QuartLDetectorSD::QuartLDetectorSD(G4String name) :
  G4VSensitiveDetector(name), fRunAction(0), fOutput(0), fEvent(0)
{
  G4cout << __PRETTY_FUNCTION__ << " new sensitive detector with name \"" << GetName() << "\" initialized" << G4endl;
  fRunAction = (RunAction*)G4RunManager::GetRunManager()->GetUserRunAction();
  fOutput = (FileWriter*)fRunAction->GetFileWriter();
  fEvent = new PPS::QuartLEvent(GetName());
  fOutput->RegisterSD(fEvent);
}

QuartLDetectorSD::~QuartLDetectorSD()
{
  //if (fEvent) delete fEvent; // FIXME FIXME FIXME
}

void
QuartLDetectorSD::Initialize(G4HCofThisEvent*)
{
  fEvent->Clear();
}

G4bool
QuartLDetectorSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  // FIXME ! Need to isolate such events (loopers, ... ?)
  //if (fOutput->GetNumHitsInEvent()>MAX_HITS) return false;

  if (step->GetTrack()->GetDefinition()==G4OpticalPhoton::OpticalPhotonDefinition()) {
    //fOutput->AddHitInEvent(step);
    fEventTime = step->GetPreStepPoint()->GetGlobalTime();
    G4Track* track = step->GetTrack();
    //fEvent->AddPhoton(step);
    G4ThreeVector mom3 = track->GetMomentum(), pos3 = track->GetPosition();
    
    TLorentzVector mom(mom3.x(), mom3.y(), mom3.z(), track->GetTotalEnergy());
    TLorentzVector pos(pos3.x(), pos3.y(), pos3.z(), track->GetGlobalTime());
    
    fEvent->AddPhoton(pos, mom);
    
    track->SetTrackStatus(fStopAndKill); // One kills the particle after its arrival in the sensitive detector
  }
 
  return true;
}


void
QuartLDetectorSD::EndOfEvent(G4HCofThisEvent*)
{
  //G4cout << __PRETTY_FUNCTION__ << " " << fEvent->GetNumberOfPhotons() << " photon hits in this event" << G4endl;

  // Filling the tree with kinematic information...
  fOutput->AddSDData<PPS::QuartLEvent>(GetName(), fEvent);
}

