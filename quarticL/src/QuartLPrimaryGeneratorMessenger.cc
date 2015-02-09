#include "QuartLPrimaryGeneratorMessenger.hh"

QuartLPrimaryGeneratorMessenger::QuartLPrimaryGeneratorMessenger(QuartLPrimaryGeneratorAction* pga):
  fAction(pga)
{
  fPolarCmd = new G4UIcmdWithADoubleAndUnit("/gun/optPhotonPolar", this);
  fPolarCmd->SetGuidance("Set linear polarization");
  fPolarCmd->SetGuidance("  angle w.r.t. (k,n) plane");
  fPolarCmd->SetParameterName("angle", true);
  fPolarCmd->SetUnitCategory("Angle");  
  fPolarCmd->SetDefaultValue(-360.0);
  fPolarCmd->SetDefaultUnit("deg");
  fPolarCmd->AvailableForStates(G4State_Idle);
  
  fInputFilename = new G4UIcmdWithAString("/gun/inputROOTFile", this);
  fInputFilename->SetGuidance("Set the input ROOT tree");
  fInputFilename->SetGuidance(" used to generate the hits");
  fInputFilename->SetParameterName("input", true);
  fInputFilename->AvailableForStates(G4State_PreInit, G4State_Idle);
}

QuartLPrimaryGeneratorMessenger::~QuartLPrimaryGeneratorMessenger()
{
  delete fPolarCmd;
  delete fInputFilename;
}

void
QuartLPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String value)
{ 
  if (command==fPolarCmd) {
    G4double angle = fPolarCmd->GetNewDoubleValue(value);
    if (angle==-360.0) fAction->SetOptPhotonPolar();
    else fAction->SetOptPhotonPolar(angle);
  }
  else if (command==fInputFilename) {
    if (!fAction->SetInputROOTFile(value)) {
      std::ostringstream ss;
      ss << "Error while loading the TTree \"hits\" in ROOT input file \"" << value << "\"" << G4endl;
      G4Exception("QuartLPrimaryGeneratorMessenger::SetNewValue", "InvalidFilename", JustWarning, ss);
    }
  }
}
