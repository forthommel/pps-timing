#include "RunAction.hh"

namespace PPS
{
  RunAction::RunAction(FileWriter* analyzer) :
    fOutput(analyzer)
  {
    fTimer = new G4Timer;
    fMaterialManager = new MaterialManager;
    fRunInfo = static_cast<RunInformation*>(fOutput->GetRunInformation());
  }
  
  RunAction::~RunAction()
  {
    delete fTimer;
    delete fMaterialManager;
  }
  
  void
  RunAction::BeginOfRunAction(const G4Run* aRun)
  {
    G4cerr << "##### Run " << aRun->GetRunID() << " is starting ! #####" << G4endl;
    fOutput->GetEventInformation()->BeforeRun();
    fTimer->Start();
  }
  
  void
  RunAction::EndOfRunAction(const G4Run* aRun)
  {   
    fTimer->Stop();
    G4cerr << " Number of events = "
	   << aRun->GetNumberOfEvent() << G4endl
	   << " Timing : " << *fTimer << G4endl;
    fOutput->StoreRun();
  }
}
