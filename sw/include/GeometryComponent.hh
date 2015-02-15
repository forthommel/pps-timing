#ifndef GeometryComponent_h
#define GeometryComponent_h

#include "G4VPhysicalVolume.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"

#include "RunAction.hh"

class GeometryComponent
{
  public:
    GeometryComponent(G4String name);
    ~GeometryComponent();

    virtual G4VPhysicalVolume* Construct();
    inline void SetParentLog(G4LogicalVolume* parent) { fParentLog=parent; }
    inline void SetParentPhys(G4VPhysicalVolume* parent) { fParentPhys=parent; }
    inline void SetCenter(G4ThreeVector center) { fPosition=center; }
    inline void SetSDname(G4String name) { fSDname=name; if(name!="") fIsSensitive=true; }
    inline virtual void BeforeConstruct() {;}
  
  protected:
    G4String fName;
    MaterialManager* fMaterial;

    G4ThreeVector fPosition;
    G4LogicalVolume* fParentLog;
    G4VPhysicalVolume* fParentPhys;
    G4VPhysicalVolume* fPhys;

    G4bool fIsSensitive;
    G4String fSDname;

    void* fEvent;
};

#endif
