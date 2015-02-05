#ifndef DetectorSD_h
#define DetectorSD_h

#include "QuartLRunAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4VSensitiveDetector.hh"

class G4Step;
class RunAction;

class DetectorSD: public G4VSensitiveDetector 
{
  public:
    DetectorSD(G4String);
    ~DetectorSD();

    void Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    void EndOfEvent(G4HCofThisEvent*);
    
  private:
    QuartLRunAction* runAction;
    
    G4double detEnergy;
    /** Track time */
    G4double detTime;
    /** Time of arrival for the first photon */
    G4double firstPh;
};

#endif
