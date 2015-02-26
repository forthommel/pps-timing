#include "TrackingAction.hh"

namespace PPS
{
  TrackingAction::TrackingAction()
  {}
  
  TrackingAction::~TrackingAction()
  {}
  
  void
  TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
  {
    if(!aTrack->GetParentID() and !aTrack->GetUserInformation()) {
      TrackInformation* extra_info = new TrackInformation(aTrack);
      G4Track* track = (G4Track*)aTrack;
      track->SetUserInformation(extra_info);
    }
  }
  
  void
  TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
  {
    G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
    if (secondaries) {
      TrackInformation* info = (TrackInformation*)(aTrack->GetUserInformation());
      size_t nSeco = secondaries->size();
      if (nSeco>0) {
	for(size_t i=0; i<nSeco; i++) {
	  TrackInformation* infoNew = new TrackInformation(info);
	  (*secondaries)[i]->SetUserInformation(infoNew);
	}
      }
    }
  }
}
