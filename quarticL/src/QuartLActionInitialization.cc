#include "QuartLActionInitialization.hh"

QuartLActionInitialization::QuartLActionInitialization() :
  G4VUserActionInitialization()
{
  // UserAction classes
  //
  fPrimaryGenerator = new QuartLPrimaryGeneratorAction;
  fRunAction = new QuartLRunAction;
  fEventAction = new QuartLEventAction;
  fStackingAction = new QuartLStackingAction;
}

QuartLActionInitialization::~QuartLActionInitialization()
{}

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
  
