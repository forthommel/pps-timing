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
#include "G4GDMLParser.hh"
#include "globals.hh"

#include "MaterialManager.hh"
#include "GeometryConstructorMessenger.hh"
#include "GeometryComponent.hh"

namespace PPS
{  
  typedef std::vector<GeometryComponent*> ComponentsRef;
  class GeometryConstructorMessenger;
  /**
   * Detectors (and geometry) manager.
   *
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date Feb 2015
   */
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
       * \return Unique identifier of the component for a later usage.
       */
      G4int AddNewComponent(G4String type="");
      /**
       * Set the location of one given component
       * \param[in] id GeometryComponent unique identifier in this geometry
       * \param[in] pos Location of the component's center
       * \return A boolean stating the success or error of the operation.
       */
      G4bool MoveComponent(G4int id=-1, G4ThreeVector pos=G4ThreeVector(0., 0., 0.));
      /**
       * Rotate the component around the x axis.
       * \param[in] id GeometryComponent unique identifier in this geometry
       * \return A boolean stating the success or error of the operation.
       */
      G4bool RotateComponentTheta(G4int id=-1, G4double theta=0.);
      /**
       * Rotate the component around the z axis.
       * \param[in] id GeometryComponent unique identifier in this geometry
       * \return A boolean stating the success or error of the operation.
       */
      G4bool RotateComponentPhi(G4int id=-1, G4double phi=0.);
      /**
       * Set the name of the sensitive detector attached to one geometry component
       * \param[in] id GeometryComponent unique identifier in this geometry
       * \param[in] name Sensitive detector's name for the GeometryComponent object
       * \return A boolean stating the success or error of the operation.
       */
      G4bool SetSDname(G4int id=-1, G4String name="");

      void WriteGDML(G4String filename="geometry.gdml");

      void LoadGDML(G4String filename="geometry.gdml");
  
    private:
      /**
       * Build the physical volume given the geometry information provided by the messenger
       * \return A pointer to the physical volume setting the geometry
       */
      G4VPhysicalVolume* ConstructGeometry();
    
      G4double expHall_x;
      G4double expHall_y;
      G4double expHall_z;

      G4VPhysicalVolume* expHall_phys;
      G4LogicalVolume* expHall_log;

      MaterialManager *fMaterial;
      GeometryConstructorMessenger *fMessenger;

      /// Set of pointers to the components to be added in the geometry.
      ComponentsRef fComponents;
      /// Components location (defined wrt. the mother physical volume)
      std::vector<G4ThreeVector> fComponentsLocation;
      /// Workaround to avoid building multiple times the same detector in the geometry update process.
      std::vector<bool> fComponentsBuilt;
  };
}

#endif
