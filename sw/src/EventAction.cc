#include "EventAction.hh"
 
EventAction::EventAction()
{}
 
EventAction::~EventAction()
{}
 
void
EventAction::BeginOfEventAction(const G4Event* event)
{
  const G4int num_events = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
  G4cout << "\tEvent " << event->GetEventID()+1 << " / " << num_events << G4endl;
}
 
void
EventAction::EndOfEventAction(const G4Event*)
{
  //G4cout << __PRETTY_FUNCTION__ << G4endl;
  ((RunAction*)G4RunManager::GetRunManager()->GetUserRunAction())->GetFileWriter()->Store();
}

