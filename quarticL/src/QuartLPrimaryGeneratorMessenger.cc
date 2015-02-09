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
  
  fProbeCell = new G4UIcmdWith3Vector("/gun/probeCell", this);
  fProbeCell->SetGuidance("Probe an individual Quartic cell");
  fProbeCell->SetGuidance(" by sending a single proton towards its center");
  fProbeCell->SetParameterName("stationId", "cellId", "energy", true);
  fProbeCell->SetDefaultValue(G4ThreeVector(0, 0, 100.*CLHEP::GeV));
  fProbeCell->AvailableForStates(G4State_Idle);
}

QuartLPrimaryGeneratorMessenger::~QuartLPrimaryGeneratorMessenger()
{
  delete fPolarCmd;
  delete fInputFilename;
  delete fProbeCell;
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
      ss << "Error while loading the TTree \"hits\" in ROOT input file \"" << value << "\"";
      G4Exception("QuartLPrimaryGeneratorMessenger::SetNewValue", "InvalidFilename", JustWarning, ss);
    }
  }
  else if (command==fProbeCell) {
    G4ThreeVector val = fProbeCell->GetNew3VectorValue(value);
    G4int station_id = static_cast<G4int>(val.x());
    G4int cell_id = static_cast<G4int>(val.y());
    if (!fAction->ProbeOneCell(station_id, cell_id, val.z())) {
      std::ostringstream ss;
      ss << "Error while trying to probe the cell " << cell_id
         << " on station " << station_id
         << " with protons of " << val.z()/CLHEP::GeV << " GeV";
      G4Exception("QuartLPrimaryGeneratorMessenger::SetNewValue", "InvalidCellProbe", JustWarning, ss);
    }
  }
}
