#include "Component.hh"

Component::Component() :
  fParentLog(0), fParentPhys(0), fPhys(0)
{
}

Component::~Component()
{}

G4VPhysicalVolume*
Component::Construct()
{
  return fPhys;
}
