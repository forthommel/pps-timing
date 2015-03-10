#include "QuartLDetectorSD.hh"

using namespace CLHEP;

namespace Quartic
{
  QuartLDetectorSD::QuartLDetectorSD(G4String name) :
    PPS::SensitiveDetector<QuartLEvent>(name)
  {
    RegisterEvent();
  }

  QuartLDetectorSD::~QuartLDetectorSD()
  {}
  
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

      QuartLPhotonHit* hit = new QuartLPhotonHit;
      hit->SetIncomingParticle(fRunAction->GetRunInformation()->GetIncomingParticle(ti->GetOriginalTrackID()-1));
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

      fEvent->AddPhoton(hit);

      // One kills the particle after its arrival in the sensitive detector
      track->SetTrackStatus(fStopAndKill);
    }

    return true;
  }
}
