#include "ActionInitialization.hh"

namespace PPS
{
  ActionInitialization::ActionInitialization() :
    G4VUserActionInitialization()
  {
    fPrimaryGenerator = new PrimaryGeneratorAction;
    fOutput = new FileWriter;
    fEventAction = new EventAction;
    fStackingAction = new StackingAction;
    fTrackingAction = new TrackingAction;
  }
  
  ActionInitialization::~ActionInitialization()
  {
    delete fOutput;
  }
  
  void
  ActionInitialization::BuildForMaster() const
  {
    RunAction* fRunAction = new RunAction(fOutput);
    SetUserAction(fRunAction);
  }
  
  void
  ActionInitialization::Build() const
  {
    RunAction* fRunAction = new RunAction(fOutput);
    SetUserAction(fPrimaryGenerator);
    SetUserAction(fRunAction);
    SetUserAction(fEventAction);
    SetUserAction(fStackingAction);
    SetUserAction(fTrackingAction);
  }
}
  
