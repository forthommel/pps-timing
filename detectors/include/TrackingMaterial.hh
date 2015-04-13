#ifndef TrackingMaterial_h
#define TrackingMaterial_h

#include "G4Box.hh"

#include "GeometryComponent.hh"
#include "SensitiveDetector.hh"

#include "TH1.h"

class TrackingMaterialMessenger;
class TrackingMaterialSD;
class TrackingMaterial : public PPS::GeometryComponent
{
  public:
    TrackingMaterial(G4String name="");
    ~TrackingMaterial();

    void BeforeConstruct();
    
    void SetThickness(G4double th) { fThickness=th; }
    
  private:
    G4VPhysicalVolume* BuildOneStation();
    TrackingMaterialMessenger *fMessenger;
    TrackingMaterialSD* fSD;
    
    G4double fThickness;
};

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh" 

class TrackingMaterialMessenger : public G4UImessenger
{
  public:
    TrackingMaterialMessenger(TrackingMaterial*);
    ~TrackingMaterialMessenger();

    void SetNewValue(G4UIcommand*, G4String);

  private:
    TrackingMaterial *fTM;

    G4UIdirectory* fTMDir;
    G4UIcmdWithADoubleAndUnit* fThickness;
    /*G4UIcmdWithAString* fAddComponent;
    G4UIcmdWith3VectorAndUnit* fComponentPosition;
    G4UIcmdWithADoubleAndUnit* fComponentRotationPhi;
    G4UIcmdWithoutParameter* fUpdateGeometry;*/
};

#include "EnvironmentalEvent.h"

class TrackingMaterialSD : public PPS::SensitiveDetector<EnvironmentalEvent>
{
  public:
    TrackingMaterialSD(G4String);
    virtual ~TrackingMaterialSD();

    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    //G4bool Hit(G4Step*);
};

#endif
