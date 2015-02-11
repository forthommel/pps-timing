#ifndef QuartLEventAction_h
#define QuartLEventAction_h

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "G4UserEventAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"

#include "QuartLRunAction.hh"

class G4Event;

class QuartLEventAction : public G4UserEventAction
{
  public:
    QuartLEventAction();
   ~QuartLEventAction();

  public:
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
};

#endif
