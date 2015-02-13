#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization() :
  G4VUserActionInitialization()
{
  //
  // UserAction classes
  //
  fPrimaryGenerator = new PrimaryGeneratorAction;
  fEventAction = new EventAction;
  fStackingAction = new StackingAction;
  fOutput = new FileWriter;
}

ActionInitialization::~ActionInitialization()
{
  delete fOutput;
}

void
ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction(fOutput));
}

void
ActionInitialization::Build() const
{
  SetUserAction(fPrimaryGenerator);
  SetUserAction(new RunAction(fOutput));
  SetUserAction(fEventAction);
  SetUserAction(fStackingAction);
}
  
