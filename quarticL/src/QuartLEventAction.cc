#include "QuartLEventAction.hh"
 
QuartLEventAction::QuartLEventAction()
{}
 
QuartLEventAction::~QuartLEventAction()
{}
 
void
QuartLEventAction::BeginOfEventAction(const G4Event*)
{}
 
void
QuartLEventAction::EndOfEventAction(const G4Event* event)
{
  G4cout << "\tEvent #" << event->GetEventID() << G4endl;
}

