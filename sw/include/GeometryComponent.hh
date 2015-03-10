#ifndef GeometryComponent_h
#define GeometryComponent_h

#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"

#include "RunAction.hh"

#include <string>

#define BUILDERNM(obj) obj ## Builder
#define REGISTER_COMPONENT(obj,type) class BUILDERNM(obj) : public PPS::GeometryComponentBuilder { public: BUILDERNM(obj)() { PPS::GeometryComponentStore::GetInstance()->AddComponent(type,this); } virtual PPS::GeometryComponent* Build(std::string name) { return new obj(name); } }; static BUILDERNM(obj) g ## obj;

namespace PPS
{
  class GeometryComponentBuilder;
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
      GeometryComponent(G4String="");
      ~GeometryComponent();

      inline std::string GetName() const { return static_cast<std::string>(fName); }
      /**
       * \brief Set the mother logical volume associated to this component.
       */
      inline void SetParentLog(G4LogicalVolume* parent) { fParentLog=parent; }
      /**
       * \brief Set the mother physical volume associated to this component.
       */
      inline void SetParentPhys(G4VPhysicalVolume* parent) { fParentPhys=parent; }
      /**
       * \brief Set the position of this component, with respect to its mother volume.
       */
      inline void SetCenter(G4ThreeVector center) { fPosition=center; }
      /**
       * \brief Set the polar rotation of this component, with respect to its mother volume.
       */
      inline void RotateTheta(G4double theta) { fRotation.rotateX(theta); }
      /**
       * \brief Set the azimuthal rotation of this component, with respect to its mother volume.
       */
      inline void RotatePhi(G4double phi) { fRotation.rotateZ(phi); }
      /**
       * Set the sensitive detector name of this component, automatically setting it as a sensitive
       * (active) component.
       * \brief Set the Sensitive detector name of this component.
       */
      inline void SetSDname(G4String name) { fSDname=name; if(!name.empty()) fIsSensitive=true; }
      /**
       * Method to be ran before constructing the physical volume of this component.
       * Typically this can be used to compute additional distances, angles, ... based
       * on user-controlled quantities set by a messenger.
       * \brief Pre-constructor method (compute last quantities/dimensions/... before setting
       * the physical volume).
       */
      inline virtual void BeforeConstruct() {;}
      /**
       * \brief Build the physical volume associated to the geometry component.
       */
      virtual G4VPhysicalVolume* Construct();
  
    protected:
      /// Get the name of the logical volume surrounding this component.
      G4String GetLogName() const {
        std::ostringstream out;
        out << GetName() << "_container_log";
        return out.str();
      }
      /// Get the name of the physical volume surrounding this component.
      G4String GetPhysName() const {
        std::ostringstream out;
        out << GetName() << "_container_phys";
        return out.str();
      }
      /// Name of this component
      const G4String fName;
      /// Instance of the materials manager object to be used to define the component
      const MaterialManager* fMaterial;

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

  /**
   * \brief Builder class for a GeometryComponent object from the store.
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date 9 Mar 2015 
   */
  class GeometryComponentBuilder
  {
    public:
      /// Create one GeometryComponent out of this builder.
      virtual GeometryComponent* Build(std::string)=0;
  };

  /**
   * Static object filled with all available GeometryComponent objects
   * which can be constructed and added to the spectrometer geometry.
   * 
   * \brief Store full of GeometryComponent objects.
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   * \date 9 Mar 2015 
   */
  class GeometryComponentStore
  {
    private:
      GeometryComponentStore() {;}
      /// The static object present everywhere at runtime.
      static GeometryComponentStore* fComponentsStore;
      /// A boolean stating whether or not the static object is already
      /// built.
      static bool fBuilt;

    public:
      typedef std::vector<std::string> Names;
      /// The core of this components store : a map between the unique
      /// component's name and its builder.
      typedef std::map<std::string, GeometryComponentBuilder*> Map;
      typedef std::pair<std::string, GeometryComponentBuilder*> Pair;
      
      ~GeometryComponentStore() { fBuilt=false; }
      static GeometryComponentStore* GetInstance();
      
      /**
       * \brief Add a new component to the present store instance.
       * \param[in] type A unique name identifying the component.
       * \param[in] comp A builder object to store for future instance
       * creation(s).
       */
      void AddComponent(std::string,GeometryComponentBuilder*);
      
      /// Retrieve the number of unique components which can be built by
      /// this instance.
      inline size_t GetNumRegisteredComponents() const { return fMap.size(); }
      /// Retrieve a list of registered components names.
      Names GetRegisteredComponents() const;
      /// Retrieve one component from the store by its unique name.
      GeometryComponentBuilder* GetByType(std::string);

    private:
      Map fMap;
  };
}

#endif
