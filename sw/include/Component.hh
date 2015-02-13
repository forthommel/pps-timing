#ifndef Component_h
#define Component_h

#include "G4VPhysicalVolume.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"

#include "RunAction.hh"
#include "DetectorSD.hh"

class Component
{
  public:
    Component(G4String name);
    ~Component();

    virtual G4VPhysicalVolume* Construct();
    inline void SetParentLog(G4LogicalVolume* parent) { fParentLog=parent; }
    inline void SetParentPhys(G4VPhysicalVolume* parent) { fParentPhys=parent; }
    inline void SetComponentCenter(G4ThreeVector center) { fPosition=center; }
    inline void SetSDname(G4String name) { fSDname=name; if(name!="") fIsSensitive=true; }
    inline virtual void BeforeConstruct() {;}
  
  protected:
    G4String fName;
    MaterialManager* fMaterial;
    DetectorSD* fSD;

    G4ThreeVector fPosition;
    G4LogicalVolume* fParentLog;
    G4VPhysicalVolume* fParentPhys;
    G4VPhysicalVolume* fPhys;

    G4bool fIsSensitive;
    G4String fSDname;
};

#endif
