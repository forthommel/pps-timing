#ifndef GeometryConstructor_h
#define GeometryConstructor_h

#include "G4PVReplica.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

#include "G4PVPlacement.hh"
#include "G4Box.hh"

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "MaterialManager.hh"
#include "GeometryConstructorMessenger.hh"

class GeometryConstructorMessenger;

class GeometryConstructor : public G4VUserDetectorConstruction
{
  public:
    GeometryConstructor();
    ~GeometryConstructor();
    
    G4VPhysicalVolume* Construct();

  private:
    
    G4double expHall_x;
    G4double expHall_y;
    G4double expHall_z;

    G4VPhysicalVolume* expHall_phys;
    G4LogicalVolume* expHall_log;

    MaterialManager *fMaterial;
    GeometryConstructorMessenger *fMessenger;
};

#endif
