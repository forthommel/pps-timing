#include "GeometryConstructorMessenger.hh"

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

  fComponentSDname = new G4UIcmdWithAString("/PPS/componentSDname", this);
  fComponentSDname->SetParameterName("component_sensitivedetector_name", true);
  fComponentSDname->AvailableForStates(G4State_PreInit, G4State_Idle);

  fUpdateGeometry = new G4UIcmdWithoutParameter("/PPS/updateGeometry", this);
  fUpdateGeometry->AvailableForStates(G4State_PreInit, G4State_Idle);
}

GeometryConstructorMessenger::~GeometryConstructorMessenger()
{
  delete fPPSDir;
  delete fAddComponent;
  delete fComponentPosition;
  delete fComponentSDname;
  delete fUpdateGeometry;
}

void
GeometryConstructorMessenger::SetNewValue(G4UIcommand* command, G4String value)
{
  if (command==fAddComponent) {
    G4cout << __PRETTY_FUNCTION__ << " Adding a new component to the geometry : " << value << G4endl;
    if (value=="QUARTIC" or value=="MBP") {
      fLastComponentAdded = fDC->AddNewComponent(value);
    }
    else {
      std::ostringstream ss;
      ss << "Error while trying to add a component to the run." << G4endl
         << "Component name \"" << value << "\" is invalid !";
      G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
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
  else if (command==fComponentSDname) {
    if (fLastComponentAdded<0) {
      std::ostringstream ss;
      ss << "Error while trying to set a previously added component's sensitive detector name." << G4endl
         << "Invalid component id (" << fLastComponentAdded << "). Check the addition procedure !";
      G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
    }
  }
  else if (command==fUpdateGeometry) {
    G4cout << __PRETTY_FUNCTION__ << " Updating the global geometry" << G4endl;
    fDC->UpdateGeometry();
  }
}
