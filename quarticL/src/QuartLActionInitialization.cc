#include "QuartLActionInitialization.hh"

QuartLActionInitialization::QuartLActionInitialization() :
  G4VUserActionInitialization()
{
  //fAnalyzer = new QuartLAnalyzer;
  //
  // UserAction classes
  //
  fPrimaryGenerator = new QuartLPrimaryGeneratorAction;
  //fRunAction = new QuartLRunAction(new QuartLAnalyzer);
  fEventAction = new QuartLEventAction;
  fStackingAction = new QuartLStackingAction;
}

QuartLActionInitialization::~QuartLActionInitialization()
{
  //delete fAnalyzer;
}

void
QuartLActionInitialization::BuildForMaster() const
{
  SetUserAction(new QuartLRunAction(new QuartLAnalyzer));
}

void
QuartLActionInitialization::Build() const
{
  SetUserAction(fPrimaryGenerator);
  //SetUserAction(new QuartLRunAction(fAnalyzer));
  SetUserAction(new QuartLRunAction(new QuartLAnalyzer));
  SetUserAction(fEventAction);
  SetUserAction(fStackingAction);
}
  
