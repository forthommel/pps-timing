#include "QuartLDetectorSD.hh"

using namespace CLHEP;

namespace Quartic
{
  QuartLDetectorSD::QuartLDetectorSD(G4String name) :
    G4VSensitiveDetector(name), fRunAction(0), fOutput(0), fEvent(0)
  {
    G4cout << __PRETTY_FUNCTION__ << " new sensitive detector with name \"" << GetName() << "\" initialized" << G4endl;
    fRunAction = (PPS::RunAction*)G4RunManager::GetRunManager()->GetUserRunAction();
    fOutput = (PPS::FileWriter*)fRunAction->GetFileWriter();
    fEvent = new QuartLEvent(GetName());
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
      fEventTime = step->GetPreStepPoint()->GetGlobalTime();
      G4Track* track = step->GetTrack();
      G4ThreeVector mom3 = track->GetMomentum(), pos3 = track->GetPosition();
      PPS::TrackInformation* ti = static_cast<PPS::TrackInformation*>(track->GetUserInformation());
      
      //G4cout << __PRETTY_FUNCTION__ << " --> track " << track->GetTrackID() << " has parent " << ti->GetOriginalTrackID() << G4endl;
      
      QuartLPhotonHit *hit = new QuartLPhotonHit(ti->GetOriginalTrackID());
      hit->SetCellID(step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo());
      hit->SetMomentum(TLorentzVector(
        mom3.x()/GeV,
        mom3.y()/GeV,
        mom3.z()/GeV,
        track->GetTotalEnergy()/GeV
      ));
      hit->SetPosition(TLorentzVector(
        pos3.x()/m,
        pos3.y()/m,
        pos3.z()/m,
        track->GetGlobalTime()/second
      ));
      hit->SetIncomingParticle(fRunAction->GetRunInformation()->GetIncomingParticle(ti->GetOriginalTrackID()-1));
      
      fEvent->AddPhoton(hit);
      
      // One kills the particle after its arrival in the sensitive detector
      track->SetTrackStatus(fStopAndKill);
    }
    
    return true;
  }
  
  
  void
  QuartLDetectorSD::EndOfEvent(G4HCofThisEvent*)
  {
    //G4cout << __PRETTY_FUNCTION__ << " " << fEvent->GetNumberOfPhotons() << " photon hits in this event" << G4endl;
    
    // Filling the tree with kinematic information...
    fOutput->AddSDData<Quartic::QuartLEvent>(GetName(), fEvent);
  }
}
