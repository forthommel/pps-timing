#include "QuartLStackingAction.hh"

QuartLStackingAction::QuartLStackingAction():
  gammaCounter(0)
{
  G4cout <<" QuartLStackingAction() called..." << G4endl;
}

QuartLStackingAction::~QuartLStackingAction()
{}

G4ClassificationOfNewTrack
QuartLStackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
    // particle is optical photon
    if(aTrack->GetParentID()>0) {
      // particle is secondary
      gammaCounter++;
    }
  }
  return fUrgent;
}

void
QuartLStackingAction::NewStage()
{
  // was G4cout << "Number of optical photons produced in this event : "
  // was        << gammaCounter << G4endl;
}

void
QuartLStackingAction::PrepareNewEvent()
{
  gammaCounter = 0;
}
