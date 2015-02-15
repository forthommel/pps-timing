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
  
