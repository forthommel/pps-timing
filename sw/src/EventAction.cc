#include "EventAction.hh"
 
namespace PPS
{
  EventAction::EventAction()
  {
    fTimer = new G4Timer;
  }
 
  EventAction::~EventAction()
  {
    delete fTimer;
  }
 
  void
  EventAction::BeginOfEventAction(const G4Event* event)
  {
    const G4int num_events = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
    G4cout << "\tEvent " << event->GetEventID()+1 << " / " << num_events << G4endl;
    fTimer->Start();
  }
 
  void
  EventAction::EndOfEventAction(const G4Event*)
  {
    //G4cout << __PRETTY_FUNCTION__ << G4endl;
    FileWriter* wr = static_cast<FileWriter*>(((RunAction*)G4RunManager::GetRunManager()->GetUserRunAction())->GetFileWriter());
    fTimer->Stop();
    wr->GetEventInformation()->SetGenerationTime(fTimer->GetSystemElapsed());
    wr->StoreEvent();
  }
}

