#ifndef QuartLDetectorSD_h
#define QuartLDetectorSD_h

#include "RunAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4VSensitiveDetector.hh"
#include "globals.hh"

#include "FileWriter.hh"

#include "QuartLEvent.h"

class G4Step;
class RunAction;

class QuartLDetectorSD: public G4VSensitiveDetector 
{
  public:
    QuartLDetectorSD(G4String);
    ~QuartLDetectorSD();
  
    void Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    void EndOfEvent(G4HCofThisEvent*);
    
  private:
    RunAction* fRunAction;
    FileWriter *fOutput;

    PPS::QuartLEvent *fEvent;

    time_t fEventTime;
};

#endif
