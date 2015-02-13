#include "Component.hh"

Component::Component(G4String name) :
  fName(name), fParentLog(0), fParentPhys(0), fPhys(0)
{
  fMaterial = new MaterialManager;
}

Component::~Component()
{
  delete fMaterial;
}

G4VPhysicalVolume*
Component::Construct()
{
  G4cout << __PRETTY_FUNCTION__ << " Building a new component with name \"" << fName << "\"" << G4endl;
  return fPhys;
}
