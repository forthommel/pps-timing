#ifndef QuartLDetector_h
#define QuartLDetector_h

#include "G4Box.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalBorderSurface.hh"

#include "GeometryComponent.hh"
#include "ComponentsMap.hh"

#include "QuartLDetectorSD.hh"

#define MAX_BARS 20

namespace Quartic
{
  /**
   * \brief Main constructor for the L-bar QUARTIC Geant4 geometry
   *
   * \author Vladimir Samoilenko <vladimir.samoilenko@cern.ch>
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class QuartLDetector : public PPS::GeometryComponent
  {
    public:
      QuartLDetector(G4String name);
      virtual ~QuartLDetector();
      static G4String GetType() { return "QUARTIC"; }

      void BeforeConstruct();
      G4ThreeVector GetCellCenter(G4int cell_id) const;

    private:
      /**
       * \brief Generate and add material properties table
       */
      void BuildOpticalProperties();

      QuartLDetectorSD* fSD;

      G4VPhysicalVolume* BuildOneStation();

      G4int fNumBars;
    
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

      G4Box* BarV[MAX_BARS];
      G4Box* BarH[MAX_BARS];
      G4UnionSolid* Bar[MAX_BARS];
      G4LogicalVolume* Bar_log[MAX_BARS];
      G4VPhysicalVolume* Bar_phys[MAX_BARS];
      G4LogicalBorderSurface* SilAirBord[MAX_BARS];
      G4LogicalBorderSurface* PMSilSurf[MAX_BARS];
      G4LogicalVolume* window_log[MAX_BARS];
      G4VPhysicalVolume* window_phys[MAX_BARS];

      G4Material* fContainerMaterial;
  };
}

#endif
