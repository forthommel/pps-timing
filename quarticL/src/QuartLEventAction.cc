#include "QuartLEventAction.hh"
 
QuartLEventAction::QuartLEventAction()
{}
 
QuartLEventAction::~QuartLEventAction()
{}
 
void
QuartLEventAction::BeginOfEventAction(const G4Event*)
{}
 
void
QuartLEventAction::EndOfEventAction(const G4Event*)
{
  // Trajectory drawing now done by vis mananger under vis comamnds.
  // See vis.mac.
}

