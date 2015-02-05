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
  G4cout << "### Run " << aRun->GetRunID() << " is starting !" << G4endl; 
  timer->Start();
}

void
QuartLRunAction::EndOfRunAction(const G4Run* aRun)
{   
  timer->Stop();
  G4cout << " Number of events = "
         << aRun->GetNumberOfEvent() << G4endl
         << " Timing : " << *timer << G4endl;
}

