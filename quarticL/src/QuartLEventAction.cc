#include "QuartLEventAction.hh"
 
QuartLEventAction::QuartLEventAction()
{}
 
QuartLEventAction::~QuartLEventAction()
{}
 
void
QuartLEventAction::BeginOfEventAction(const G4Event* event)
{
  const G4int num_events = G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
  G4cout << "\tEvent " << event->GetEventID()+1 << " / " << num_events << G4endl;
}
 
void
QuartLEventAction::EndOfEventAction(const G4Event*)
{}

