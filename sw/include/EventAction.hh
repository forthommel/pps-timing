#ifndef EventAction_h
#define EventAction_h

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "G4UserEventAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4Timer.hh"

#include "RunAction.hh"

namespace PPS
{
  /**
   * Class containing all information on each event to be processed inside a run
   *
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date Feb 2015
   */
  class EventAction : public G4UserEventAction
  {
    public:
      EventAction();
      ~EventAction();

      void BeginOfEventAction(const G4Event*);
      void EndOfEventAction(const G4Event*);

    private:
      G4Timer *fTimer;
  };
}

#endif
