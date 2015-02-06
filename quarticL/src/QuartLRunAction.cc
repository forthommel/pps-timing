#include "G4Timer.hh"
#include "G4Run.hh"

#include "QuartLRunAction.hh"

QuartLRunAction::QuartLRunAction(QuartLAnalyzer* analyzer) :
  fAnalyzer(analyzer)
{
  fTimer = new G4Timer;
}

QuartLRunAction::~QuartLRunAction()
{
  delete fTimer;
}

void
QuartLRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " is starting !" << G4endl;
  fTimer->Start();
}

void
QuartLRunAction::EndOfRunAction(const G4Run* aRun)
{   
  fTimer->Stop();
  G4cout << " Number of events = "
         << aRun->GetNumberOfEvent() << G4endl
         << " Timing : " << *fTimer << G4endl;
}
