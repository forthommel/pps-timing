#ifndef BoundingBox_h
#define BoundingBox_h

#include "G4Box.hh"

#include "GeometryComponent.hh"
#include "SensitiveDetector.hh"

#include "TH1.h"

class BoundingBoxSD;
/**
 * \author Laurent Forthomme <laurent.forthomme@cern.ch>
 * \date 9 Apr 2015
 */
class BoundingBox : public PPS::GeometryComponent
{
  public:
    BoundingBox(G4String name="");
    virtual ~BoundingBox() {;}
    
    G4VPhysicalVolume* Construct() { return fPhys; }
    void BeforeConstruct();

    inline BoundingBoxSD* GetSensitiveDetector() const { return fSD; }
    
  private:
    BoundingBoxSD* fSD;
    
    bool fBuilt;
};

#include "EnvironmentalEvent.h"

/**
 * \author Laurent Forthomme <laurent.forthomme@cern.ch>
 * \date 9 Apr 2015
 */
class BoundingBoxSD : public PPS::SensitiveDetector<EnvironmentalEvent>
{
  public:
    BoundingBoxSD(G4String);
    virtual ~BoundingBoxSD();

    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};

#endif
