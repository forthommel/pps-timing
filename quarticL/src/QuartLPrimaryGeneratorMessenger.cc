#include "QuartLPrimaryGeneratorMessenger.hh"

QuartLPrimaryGeneratorMessenger::QuartLPrimaryGeneratorMessenger(QuartLPrimaryGeneratorAction* QuartLGun):
  QuartLAction(QuartLGun)
{
  gunDir = new G4UIdirectory("/quarticL/gun/");  
  gunDir->SetGuidance("PrimaryGenerator control");
   
  polarCmd = new G4UIcmdWithADoubleAndUnit("/quarticL/gun/optPhotonPolar", this);
  polarCmd->SetGuidance("Set linear polarization");
  polarCmd->SetGuidance("  angle w.r.t. (k,n) plane");
  polarCmd->SetParameterName("angle", true);
  polarCmd->SetUnitCategory("Angle");  
  polarCmd->SetDefaultValue(-360.0);
  polarCmd->SetDefaultUnit("deg");
  polarCmd->AvailableForStates(G4State_Idle);
}

QuartLPrimaryGeneratorMessenger::~QuartLPrimaryGeneratorMessenger()
{
  delete polarCmd;
  delete gunDir;
}

void
QuartLPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if (command==polarCmd) {
    G4double angle = polarCmd->GetNewDoubleValue(newValue);
    if (angle==-360.0) QuartLAction->SetOptPhotonPolar();
    else               QuartLAction->SetOptPhotonPolar(angle);
  }
}

