#ifndef TrackingAction_h
#define TrackingAction_h

#include "G4TrackingManager.hh"

#include "TrackInformation.hh"

class TrackingAction : public G4UserTrackingAction
{
  public:
    TrackingAction();
    virtual ~TrackingAction();

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);
};

#endif
