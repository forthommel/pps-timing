#ifndef MBP_h
#define MBP_h

#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4Cons.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "globals.hh"

#include "Component.hh"

typedef enum {
  STAINLESS_STEEL,
  ALBEMET,
  BERYLLIUM
} window_type;

/// Detector construction class to define materials and geometry.

class MBP : public Component
{
public:
  MBP(window_type=STAINLESS_STEEL, G4bool only_window_=false);
  virtual ~MBP();
  
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

  G4LogicalVolume *logicEnv;
  G4LogicalVolume *logicTube;
  G4LogicalVolume *logicWindow;
  
  G4VPhysicalVolume *physTube;
  G4VPhysicalVolume *physWindow;

  G4RotationMatrix *rot_taper;
  G4RotationMatrix *rot_extrusion1;
  G4RotationMatrix *rot_extrusion2;
  G4RotationMatrix *rot_window_leg1;
  G4RotationMatrix *rot_window_leg2;
  G4RotationMatrix *rot_window;

  G4Material* fWindowMaterial;
};

#endif

