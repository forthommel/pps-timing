#ifndef TrackingAction_h
#define TrackingAction_h

#include "G4TrackingManager.hh"

#include "TrackInformation.hh"

namespace PPS
{
  /**
   * Object extending the default G4 tracks to include additional run-oriented information
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class TrackingAction : public G4UserTrackingAction
  {
    public:
      TrackingAction();
      virtual ~TrackingAction();

      virtual void PreUserTrackingAction(const G4Track*);
      virtual void PostUserTrackingAction(const G4Track*);
  };
}

#endif
