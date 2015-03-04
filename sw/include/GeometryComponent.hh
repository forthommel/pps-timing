#ifndef GeometryComponent_h
#define GeometryComponent_h

#include "G4VPhysicalVolume.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"

#include "RunAction.hh"

namespace PPS
{
  /**
   * Mother object for all geometrical components defining the detector.
   * This includes passive, as well as active elements, such as beampockets
   * (Roman pots, moveable beam pipes) or detectors (QUARTICs, GasToFs, silicon
   * tracking sensors, ...)
   *
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class GeometryComponent
  {
    public:
      GeometryComponent(G4String name);
      ~GeometryComponent();

      /**
       * Build the physical volume associated to the geometry component.
       */
      virtual G4VPhysicalVolume* Construct();
      /**
       * Set the mother logical volume associated to this component.
       */
      inline void SetParentLog(G4LogicalVolume* parent) { fParentLog=parent; }
      /**
       * Set the mother physical volume associated to this component.
       */
      inline void SetParentPhys(G4VPhysicalVolume* parent) { fParentPhys=parent; }
      /**
       * Set the position of this component, with respect to its mother volume.
       */
      inline void SetCenter(G4ThreeVector center) { fPosition=center; }
      /**
       * Set the polar rotation of this component, with respect to its mother volume.
       */
      inline void RotateTheta(G4double theta) { fRotation.rotateX(theta); }
      /**
       * Set the azimuthal rotation of this component, with respect to its mother volume.
       */
      inline void RotatePhi(G4double phi) { fRotation.rotateZ(phi); }
      /**
       * Set the sensitive detector name of this component, automatically setting it as a sensitive
       * (active) component.
       */
      inline void SetSDname(G4String name) { fSDname=name; if(name!="") fIsSensitive=true; }
      /**
       * Method to be ran before constructing the physical volume of this component.
       * Typically this can be used to compute additional distances, angles, ... based
       * on user-controlled quantities set by a messenger.
       */
      inline virtual void BeforeConstruct() {;}
  
    protected:
      /// Name of this component
      G4String fName;
      /// Instance of the materials manager object to be used to define the component
      MaterialManager* fMaterial;

      /// Translation with respect to the mother volume's inner coordinate system
      G4ThreeVector fPosition;
      /// Rotation with respect to the mother volume's inner coordinate system
      G4RotationMatrix fRotation;
      /// Pointer to the mother's logical volume
      G4LogicalVolume* fParentLog;
      /// Pointer to the mother's physical volume
      G4VPhysicalVolume* fParentPhys;
      /// Pointer to this component's physical volume
      G4VPhysicalVolume* fPhys;
      /// Material used for this component's container (air, gas, ...)
      G4Material* fContainerMaterial;

      /// Is this component an active (true) or passive (false) element ?
      G4bool fIsSensitive;
      /// Name of the sensitive detector associated to this component
      G4String fSDname;

      void* fEvent;
  };
}

#endif
