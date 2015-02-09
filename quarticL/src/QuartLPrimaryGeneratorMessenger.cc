#include "QuartLPrimaryGeneratorMessenger.hh"

QuartLPrimaryGeneratorMessenger::QuartLPrimaryGeneratorMessenger(QuartLPrimaryGeneratorAction* pga):
  fAction(pga)
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
  
  fInputFilename = new G4UIcmdWithAString("/gun/inputROOTFile", this);
  fInputFilename->SetGuidance("Set the input ROOT tree");
  fInputFilename->SetGuidance(" used to generate the hits");
  fInputFilename->SetParameterName("input", true);
  fInputFilename->AvailableForStates(G4State_PreInit, G4State_Idle);
}

QuartLPrimaryGeneratorMessenger::~QuartLPrimaryGeneratorMessenger()
{
  delete polarCmd;
  delete fInputFilename;
  delete gunDir;
}

void
QuartLPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String value)
{ 
  if (command==polarCmd) {
    G4double angle = polarCmd->GetNewDoubleValue(value);
    if (angle==-360.0) fAction->SetOptPhotonPolar();
    else               fAction->SetOptPhotonPolar(angle);
  }
  else if (command==fInputFilename) {
    if (!fAction->SetInputROOTFile(value)) {
      std::ostringstream ss;
      ss << "Error while loading the TTree \"hits\" in ROOT input file \"" << value << "\"" << G4endl;
      G4Exception("QuartLPrimaryGeneratorMessenger::SetNewValue", "InvalidFilename", JustWarning, ss);
    }
  }
}
