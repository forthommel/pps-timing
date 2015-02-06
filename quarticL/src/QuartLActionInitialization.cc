#include "QuartLActionInitialization.hh"

QuartLActionInitialization::QuartLActionInitialization() :
  G4VUserActionInitialization()
{
  fAnalyzer = new QuartLAnalyzer;
  //
  // UserAction classes
  //
  fPrimaryGenerator = new QuartLPrimaryGeneratorAction;
  fRunAction = new QuartLRunAction(fAnalyzer);
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
  SetUserAction(fRunAction);
}

void
QuartLActionInitialization::Build() const
{
  SetUserAction(fPrimaryGenerator);
  SetUserAction(fRunAction);
  SetUserAction(fEventAction);
  SetUserAction(fStackingAction);
}
  
