#include "ActionInitialization.hh"

ActionInitialization::ActionInitialization() :
  G4VUserActionInitialization()
{
  //fAnalyzer = new QuartLAnalyzer;
  //
  // UserAction classes
  //
  fPrimaryGenerator = new PrimaryGeneratorAction;
  //fRunAction = new RunAction(new QuartLAnalyzer);
  fEventAction = new EventAction;
  fStackingAction = new StackingAction;
}

ActionInitialization::~ActionInitialization()
{
  //delete fAnalyzer;
}

void
ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction(new QuartLAnalyzer));
}

void
ActionInitialization::Build() const
{
  SetUserAction(fPrimaryGenerator);
  //SetUserAction(new QuartLRunAction(fAnalyzer));
  SetUserAction(new RunAction(new QuartLAnalyzer));
  SetUserAction(fEventAction);
  SetUserAction(fStackingAction);
}
  
