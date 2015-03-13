#include "GeometryConstructorMessenger.hh"

namespace PPS
{
  GeometryConstructorMessenger::GeometryConstructorMessenger(GeometryConstructor* constructor) :
    fDC(constructor), fLastComponentAdded(-1)
  {
    fPPSDir = new G4UIdirectory("/PPS/");
    fPPSDir->SetGuidance("UI commands for the PPS");
    
    fAddComponent = new G4UIcmdWithAString("/PPS/addComponent", this);
    fAddComponent->SetParameterName("component_name", true);
    fAddComponent->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    fComponentPosition = new G4UIcmdWith3VectorAndUnit("/PPS/componentPosition", this);
    fComponentPosition->SetParameterName("component_position_x", "component_position_y", "component_position_z", true);
    fComponentPosition->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    fComponentRotationTheta = new G4UIcmdWithADoubleAndUnit("/PPS/componentRotationTheta", this);
    fComponentRotationTheta->SetParameterName("component_rotation_theta", true);
    fComponentRotationTheta->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    fComponentRotationPhi = new G4UIcmdWithADoubleAndUnit("/PPS/componentRotationPhi", this);
    fComponentRotationPhi->SetParameterName("component_rotation_phi", true);
    fComponentRotationPhi->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    fComponentSDname = new G4UIcmdWithAString("/PPS/componentSDname", this);
    fComponentSDname->SetParameterName("component_sensitivedetector_name", true);
    fComponentSDname->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    fUpdateGeometry = new G4UIcmdWithoutParameter("/PPS/updateGeometry", this);
    fUpdateGeometry->AvailableForStates(G4State_PreInit, G4State_Idle);

    fGDMLOutput = new G4UIcmdWithAString("/PPS/writeGeometry", this);
    fGDMLOutput->SetParameterName("output_gdml_file", true);
    fGDMLOutput->AvailableForStates(G4State_Idle);

    fGDMLLoad = new G4UIcmdWithAString("/PPS/loadGeometry", this);
    fGDMLLoad->SetParameterName("input_gdml_file", true);
    fGDMLLoad->AvailableForStates(G4State_Idle);
  }
  
  GeometryConstructorMessenger::~GeometryConstructorMessenger()
  {
    delete fPPSDir;
    delete fAddComponent;
    delete fComponentPosition;
    delete fComponentRotationTheta;
    delete fComponentRotationPhi;
    delete fComponentSDname;
    delete fUpdateGeometry;
    delete fGDMLOutput;
    delete fGDMLLoad;
  }
  
  void
  GeometryConstructorMessenger::SetNewValue(G4UIcommand* command, G4String value)
  {
    if (command==fAddComponent) {
      G4cout << __PRETTY_FUNCTION__ << " Adding a new component to the geometry : " << value << G4endl;
      fLastComponentAdded = fDC->AddNewComponent(value);
      if (fLastComponentAdded<0) {
        std::ostringstream ss;
        ss << "Error while trying to add a component to the run." << G4endl
           << "Component name \"" << value << "\" is invalid !";
        G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", FatalErrorInArgument, ss);
      }
    }
    else if (command==fComponentPosition) {
      if (fLastComponentAdded<0) {
        std::ostringstream ss;
        ss << "Error while trying to set a previously added component's position." << G4endl
           << "Invalid component id (" << fLastComponentAdded << "). Check the addition procedure !";
        G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
      }
      if (!fDC->MoveComponent(fLastComponentAdded, fComponentPosition->GetNew3VectorValue(value))) {
        std::ostringstream ss;
        ss << "Error while trying to set a previously added component's position.";
        G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
      }
    }
    else if (command==fComponentRotationTheta) {
      if (fLastComponentAdded<0) {
        std::ostringstream ss;
        ss << "Error while trying to rotate a previously added component (theta)." << G4endl
           << "Invalid component id (" << fLastComponentAdded << "). Check the addition procedure !";
        G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
      }
      if (!fDC->RotateComponentTheta(fLastComponentAdded, -fComponentRotationTheta->GetNewDoubleValue(value))) {
        std::ostringstream ss;
        ss << "Error while trying to set a previously added component's theta rotation.";
        G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
      }
    }
    else if (command==fComponentRotationPhi) {
      if (fLastComponentAdded<0) {
        std::ostringstream ss;
        ss << "Error while trying to rotate a previously added component (phi)." << G4endl
           << "Invalid component id (" << fLastComponentAdded << "). Check the addition procedure !";
        G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
      }
      G4cout << __PRETTY_FUNCTION__ << " " << fComponentRotationPhi->GetNewDoubleValue(value) << G4endl;
      if (!fDC->RotateComponentPhi(fLastComponentAdded, -fComponentRotationPhi->GetNewDoubleValue(value))) {
        std::ostringstream ss;
        ss << "Error while trying to set a previously added component's phi rotation.";
        G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
      }
    }
    else if (command==fComponentSDname) {
      if (fLastComponentAdded<0) {
        std::ostringstream ss;
        ss << "Error while trying to set a previously added component's sensitive detector name." << G4endl
           << "Invalid component id (" << fLastComponentAdded << "). Check the addition procedure !";
        G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
      }
      if (!fDC->SetSDname(fLastComponentAdded, value)) {
        std::ostringstream ss;
        ss << "Error while trying to set a previously added component's sensitive detector name.";
        G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
      }
    }
    else if (command==fUpdateGeometry) {
      G4cout << __PRETTY_FUNCTION__ << " Updating the global geometry" << G4endl;
      fDC->UpdateGeometry();
    }
    else if (command==fGDMLOutput) {
      G4cout << __PRETTY_FUNCTION__ << " Writing the GDML dump to the file \"" << value << "\"" << G4endl;
      fDC->WriteGDML(value);
    }
    else if (command==fGDMLLoad) {
      G4cout << __PRETTY_FUNCTION__ << " Loading the GDML dump into the RunManager \"" << value << "\"" << G4endl;
      fDC->LoadGDML(value);
    }
  }
}
