#ifndef Component_h
#define Component_h

#include "G4VPhysicalVolume.hh"
#include "G4RunManager.hh"

#include "RunAction.hh"

class Component
{
public:
  Component(G4String name);
  ~Component();
  
  virtual G4VPhysicalVolume* Construct();
  inline void SetParentLog(G4LogicalVolume* parent) { fParentLog=parent; }
  inline void SetParentPhys(G4VPhysicalVolume* parent) { fParentPhys=parent; }
  inline void SetComponentCenter(G4ThreeVector center) { fPosition=center; }

protected:
  G4String fName;
  MaterialManager* fMaterial;

  G4ThreeVector fPosition;
  G4LogicalVolume* fParentLog;
  G4VPhysicalVolume* fParentPhys;
  G4VPhysicalVolume* fPhys;
};

#endif
