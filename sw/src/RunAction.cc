#include "G4Timer.hh"
#include "G4Run.hh"

#include "RunAction.hh"

RunAction::RunAction(QuartLAnalyzer* analyzer) :
  fAnalyzer(analyzer)
{
  fTimer = new G4Timer;
  fMaterialManager = new MaterialManager;
}

RunAction::~RunAction()
{
  delete fTimer;
  delete fMaterialManager;
}

void
RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "##### Run " << aRun->GetRunID() << " is starting ! #####" << G4endl;
  fTimer->Start();
}

void
RunAction::EndOfRunAction(const G4Run* aRun)
{   
  fTimer->Stop();
  G4cout << " Number of events = "
         << aRun->GetNumberOfEvent() << G4endl
         << " Timing : " << *fTimer << G4endl;
  fAnalyzer->Store();
}
