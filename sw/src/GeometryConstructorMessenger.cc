#include "GeometryConstructorMessenger.hh"

GeometryConstructorMessenger::GeometryConstructorMessenger(GeometryConstructor* constructor) :
  fDC(constructor), fLastComponentAdded(-1)
{
  fAddComponent = new G4UIcmdWithAString("/PPS/addComponent", this);
  fAddComponent->SetParameterName("component_name", true);
  fAddComponent->AvailableForStates(G4State_PreInit);

  fComponentPosition = new G4UIcmdWith3Vector("/PPS/componentPosition", this);
  fComponentPosition->SetParameterName("component_position_x", "component_position_y", "component_position_z", true);
  fComponentPosition->AvailableForStates(G4State_PreInit);
}

GeometryConstructorMessenger::~GeometryConstructorMessenger()
{
  delete fAddComponent;
  delete fComponentPosition;
}

void
GeometryConstructorMessenger::SetNewValue(G4UIcommand* command, G4String value)
{
  if (command==fAddComponent) {
    if (value=="quartic") {
    }
    else {
      std::ostringstream ss;
      ss << "Error while trying to add a component to the run." << G4endl
         << "Component name \"" << value << "\" is invalid !";
      G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
    }
  }
  if (command==fComponentPosition) {
    if (fLastComponentAdded<0) {
      std::ostringstream ss;
      ss << "Error while trying to set a previously added component's position." << G4endl
         << "Invalid component id (" << fLastComponentAdded << "). Check the addition procedure !";
      G4Exception(__PRETTY_FUNCTION__, "InvalidComponent", JustWarning, ss);
    }
  }
}
