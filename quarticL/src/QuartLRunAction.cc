#include "G4Timer.hh"
#include "G4Run.hh"

#include "QuartLRunAction.hh"

QuartLRunAction::QuartLRunAction()
{
  timer = new G4Timer;
}

QuartLRunAction::~QuartLRunAction()
{
  delete timer;
}

void
QuartLRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
  timer->Start();
}

void
QuartLRunAction::EndOfRunAction(const G4Run* aRun)
{   
  G4int iend=-2;
  G4double dummy = -2.;
  G4cout <<  iend << " " << dummy << " " << dummy << G4endl;
  
  timer->Stop();
  G4cout << " Number of event = " << aRun->GetNumberOfEvent() 
         << " " << *timer << G4endl;
}

