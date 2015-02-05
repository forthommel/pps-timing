#ifndef QuartLDetectorConstruction_h
#define QuartLDetectorConstruction_h

#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
//------------------------------------------
#include "G4UnionSolid.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
 
#include "G4Box.hh"
#include "G4PVReplica.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
//------------------------------------------
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4OpBoundaryProcess.hh"
//------------------------------------------
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
//-------------------------------------------

#include "DetectorSD.hh"

class QuartLDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    QuartLDetectorConstruction();
   ~QuartLDetectorConstruction();

  public:
    G4VPhysicalVolume* Construct();

  private:
    /** Generate and add material properties table */
    void BuildOpticalProperties();
  
    G4double expHall_x;
    G4double expHall_y;
    G4double expHall_z;

    G4double bar_x;
    G4double bar_y;
    G4double bar_z;
    /** Horizontal length for Radiator Bar */
    G4double barh_l;
    /** Vertical length for Radiator Bar */
    G4double barv_l;
    
    G4double wind_x;
    G4double wind_y;
    G4double wind_z;
    
    G4Material* Air;
    G4Material* Sil;
    G4Material* Glass;
    
    G4OpticalSurface* OpSilSurface;
};

#endif
