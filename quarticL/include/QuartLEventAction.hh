#ifndef QuartLEventAction_h
#define QuartLEventAction_h 1

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "G4UserEventAction.hh"

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

    
