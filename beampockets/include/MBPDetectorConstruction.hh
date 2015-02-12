#ifndef MBPDetectorConstruction_h
#define MBPDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"

#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4Cons.hh"
//#include "G4Orb.hh"
//#include "G4Sphere.hh"
//#include "G4Trd.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4GDMLParser.hh"

#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

typedef enum {
  STAINLESS_STEEL,
  ALBEMET,
  BERYLLIUM
} window_type;

/// Detector construction class to define materials and geometry.

class MBPDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  MBPDetectorConstruction(window_type=STAINLESS_STEEL, G4bool only_window_=false);
  virtual ~MBPDetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
  
  G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
  
protected:
  G4LogicalVolume * fScoringVolume;
private:
  G4double env_sizeXY;
  G4double env_sizeZ;
  G4double world_sizeXY;
  G4double world_sizeZ;
  
  G4double mbp_z_size;
  G4double mbp_outer_radius;
  
  G4double mbp_traptaper_z_size_small;
  G4double mbp_traptaper_z_size_large;
  G4double mbp_taper_y_size;
  G4double mbp_taper_angle;
  
  G4double mbp_cone_extrusion_depth;
  G4double mbp_cone_extrusion_angle;
  
  G4double mbp_beampipe_radius;
  G4double mbp_beampipe_extrusion_x_offset;
  G4double mbp_beampipe_sqrextrusion_x_offset;
  G4double mbp_beampipe_sqrextrusion_y_size;
  
  G4double mbp_lateral_extrusion_x_size;
  G4double mbp_lateral_extrusion_y_offset;
  
  G4double mbp_window_x_offset;
  G4double mbp_window_y_size;
  G4double mbp_window_thickness;
  G4double mbp_window_extrusion_x_size;
  G4double mbp_window_leg_length;
  
  G4bool fOnlyWindow;
  
  G4Box *solidWorld;
  G4Box *solidEnv;
  G4Tubs *solidTubeNoExtrusion;
  G4Tubs* solidBeamLineCylExtrusion;
  G4Box* solidBeamLineSqrExtrusion;
  G4UnionSolid* solidBeamLineExtrusion;
  G4Box *solidTubeHole;
  G4SubtractionSolid *solidTubeOneConeExtrusion;
  G4SubtractionSolid *solidTubeTwoConeExtrusions;
  G4SubtractionSolid *solidTubeBeamLineExtrusion;
  G4SubtractionSolid *solidTube;
  G4Box *solidHoleBox;
  G4Trap *solidTrapTaper;
  G4Box *solidSqrTaper;
  G4UnionSolid *solidTaper;
  G4Cons *solidConeExtrusion;
  G4Box *solidLateralExtrusion;
  G4Box *solidWindowExtrusion;
  
  G4Box *solidWindowLeg;
  G4Box *solidWindowCentre;
  G4UnionSolid *solidWindowOneLeg;
  G4UnionSolid *solidWindow;
  
  G4SubtractionSolid *solidMBPNoWindowExtrusion;
  G4SubtractionSolid *solidMBPNoLateralExtrusions;
  G4SubtractionSolid *solidMBPOneLateralExtrusion;
  G4SubtractionSolid *solidMBPTwoLateralExtrusions;
  G4SubtractionSolid *solidMBPNoWindow;

  G4LogicalVolume *logicWorld;
  G4LogicalVolume *logicEnv;
  G4LogicalVolume *logicTube;
  G4LogicalVolume *logicWindow;
  
  G4VPhysicalVolume *physWorld;
  G4VPhysicalVolume *physTube;
  G4VPhysicalVolume *physWindow;

  G4Material *world_mat;
  G4Material *env_mat;
  G4Material *tube_mat;
  G4Material *window_mat;

  G4RotationMatrix *rot_taper;
  G4RotationMatrix *rot_extrusion1;
  G4RotationMatrix *rot_extrusion2;
  G4RotationMatrix *rot_window_leg1;
  G4RotationMatrix *rot_window_leg2;
  G4RotationMatrix *rot_window;
  
};

#endif

