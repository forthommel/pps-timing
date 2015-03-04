#ifndef QuartLDetectorSD_h
#define QuartLDetectorSD_h

#include "SensitiveDetector.hh"

#include "QuartLEvent.h"
#include "QuartLPhotonHit.h"

namespace Quartic
{
  /**
   * Sensitive areas defined for the L-bar QUARTIC.
   *
   * \author Vladimir Samoilenko <vladimir.samoilenko@cern.ch>
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class QuartLDetectorSD : public PPS::SensitiveDetector<QuartLEvent>
  {
    public:
      QuartLDetectorSD(G4String);
      virtual ~QuartLDetectorSD();
  
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    
    private:
  };
}

#endif
