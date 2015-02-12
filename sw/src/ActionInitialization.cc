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
  fAnalyzer = new QuartLAnalyzer;
}

ActionInitialization::~ActionInitialization()
{
  delete fAnalyzer;
}

void
ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction(fAnalyzer));
}

void
ActionInitialization::Build() const
{
  SetUserAction(fPrimaryGenerator);
  SetUserAction(new RunAction(fAnalyzer));
  SetUserAction(fEventAction);
  SetUserAction(fStackingAction);
}
  
