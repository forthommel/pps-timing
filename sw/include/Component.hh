#ifndef Component_h
#define Component_h

#include "G4VPhysicalVolume.hh"

#include "MaterialManager.hh"

class Component
{
public:
  Component();
  ~Component();
  
  inline virtual G4VPhysicalVolume* Construct() { return fPhys; }
  inline void SetParentLog(G4LogicalVolume* parent) { fParentLog=parent; }
  inline void SetParentPhys(G4VPhysicalVolume* parent) { fParentPhys=parent; }
  inline void SetComponentCenter(G4ThreeVector center) { fPosition=center; }

protected:
  MaterialManager* fMaterial;

  G4ThreeVector fPosition;
  G4LogicalVolume* fParentLog;
  G4VPhysicalVolume* fParentPhys;
  G4VPhysicalVolume* fPhys;
};

#endif
