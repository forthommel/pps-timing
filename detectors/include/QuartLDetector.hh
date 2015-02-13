#ifndef QuartLDetector_h
#define QuartLDetector_h

#include "G4Box.hh"
#include "G4UnionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalBorderSurface.hh"

#include "Component.hh"
#include "DetectorSD.hh"

#define MAX_BARS 20

class QuartLDetector : public Component
{
  public:
    QuartLDetector(G4String name);
    virtual ~QuartLDetector();

    void BeforeConstruct();
  //G4VPhysicalVolume* Construct();
    G4ThreeVector GetCellCenter(G4int cell_id) const;

  private:
    /** Generate and add material properties table */
    void BuildOpticalProperties();

    G4VPhysicalVolume* BuildOneStation();
    
    G4int fNumBars;
  //G4int fNumStations;
    
  /*G4double expHall_x;
    G4double expHall_y;
    G4double expHall_z;*/

    /** x position of the Radiator Bar */
    G4double bar_x;
    /** y position of the Radiator Bar */
    G4double bar_y;
    /** z position of the Radiator Bar */
    G4double bar_z;
    /** Horizontal length for Radiator Bar */
    G4double barh_l;
    /** Vertical length for Radiator Bar */
    G4double barv_l;
    
    G4double wind_x;
    G4double wind_y;
    G4double wind_z;
    
  /*G4VPhysicalVolume* expHall_phys;
    G4LogicalVolume* expHall_log;*/
    
    G4Box* BarV[MAX_BARS];
    G4Box* BarH[MAX_BARS];
    G4UnionSolid* Bar[MAX_BARS];
    G4LogicalVolume* Bar_log[MAX_BARS];
    G4VPhysicalVolume* Bar_phys[MAX_BARS];
    G4LogicalBorderSurface* SilAirBord[MAX_BARS];
    G4LogicalBorderSurface* PMSilSurf[MAX_BARS];
    G4LogicalVolume* window_log[MAX_BARS];
    G4VPhysicalVolume* window_phys[MAX_BARS];
};

#endif
