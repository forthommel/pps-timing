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
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "globals.hh"

#include "MaterialManager.hh"
#include "GeometryConstructorMessenger.hh"

#include <vector>

////////////////////////////////////////////////////////////////
#include "detectors.hh"
#include "beampockets.hh"
////////////////////////////////////////////////////////////////

class GeometryConstructorMessenger;
typedef std::vector<Component*> ComponentsRef;

class GeometryConstructor : public G4VUserDetectorConstruction
{
  public:
    GeometryConstructor();
    ~GeometryConstructor();
    
    G4VPhysicalVolume* Construct();
    void UpdateGeometry();

    /**
     * Add a new component (detector, beampocket, ...) to the global geometry
     * \param[in] type String stating the component type
     */
    G4int AddNewComponent(G4String type="");
    /**
     * Set the location of one given component
     * \param[in] id Component unique identifier in this geometry
     * \param[in] pos Location of the component's center
     */
    G4bool MoveComponent(G4int id=-1, G4ThreeVector pos=G4ThreeVector(0., 0., 0.));
  
  private:
    
    G4double expHall_x;
    G4double expHall_y;
    G4double expHall_z;

    G4VPhysicalVolume* expHall_phys;
    G4LogicalVolume* expHall_log;

    MaterialManager *fMaterial;
    GeometryConstructorMessenger *fMessenger;

    G4VPhysicalVolume* ConstructGeometry();

    ComponentsRef fComponents;
    std::vector<G4ThreeVector> fComponentsLocation;
    /** \brief Workaround to avoid building multiple times the same detector in the geometry update process */
    std::vector<bool> fComponentsBuilt;
};

#endif
