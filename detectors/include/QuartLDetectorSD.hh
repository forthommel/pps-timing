#ifndef QuartLDetectorSD_h
#define QuartLDetectorSD_h

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4VSensitiveDetector.hh"
#include "globals.hh"

#include "FileWriter.hh"
#include "RunAction.hh"
#include "TrackInformation.hh"

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
  class QuartLDetectorSD: public G4VSensitiveDetector 
  {
    public:
      QuartLDetectorSD(G4String);
      ~QuartLDetectorSD();
  
      void Initialize(G4HCofThisEvent*);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*);
    
    private:
      PPS::RunAction* fRunAction;
      PPS::FileWriter *fOutput;

      QuartLEvent *fEvent;

      time_t fEventTime;
  };
}

#endif
