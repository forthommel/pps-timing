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
  // Trajectory drawing now done by vis mananger under vis comamnds.
  // See vis.mac.
  G4cout << "Event #" << event->GetEventID() << G4endl;
}

