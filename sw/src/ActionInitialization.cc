#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization() :
  G4VUserActionInitialization()
{
  //
  // UserAction classes
  //
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
  fOutput->SetRunInformation(fRunAction->GetRunInformation());
  SetUserAction(fRunAction);
}

void
ActionInitialization::Build() const
{
  RunAction* fRunAction = new RunAction(fOutput);
  fOutput->SetRunInformation(fRunAction->GetRunInformation());
  SetUserAction(fPrimaryGenerator);
  SetUserAction(fRunAction);
  SetUserAction(fEventAction);
  SetUserAction(fStackingAction);
  SetUserAction(fTrackingAction);
}
  
