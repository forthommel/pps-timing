#include "StackingAction.hh"

StackingAction::StackingAction():
  gammaCounter(0)
{
  G4cout <<" StackingAction() called..." << G4endl;
}

StackingAction::~StackingAction()
{}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track * aTrack)
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
StackingAction::NewStage()
{
  // was G4cout << "Number of optical photons produced in this event : "
  // was        << gammaCounter << G4endl;
}

void
StackingAction::PrepareNewEvent()
{
  gammaCounter = 0;
}
