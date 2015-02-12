#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4UImanager.hh"
#include "Randomize.hh"
#include "globals.hh"

#include "PrimaryGeneratorMessenger.hh"

#include "QuartLDetectorConstruction.hh"

#include "TFile.h"
#include "TTree.h"

class G4ParticleGun;
class G4Event;
class PrimaryGeneratorMessenger;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event*);

    void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);
    
    /**
     * Sets the input ROOT file from which all simulated events are to be fetched in private attributes.
     * \param[in] filename The ROOT file to open to fetch events
     * \return A boolean stating the success or failure of the TTree retrieval
     */
    G4bool SetInputROOTFile(G4String);
    G4bool ProbeOneQUARTICCell(G4int,G4int,G4double);

  private:
    
    G4ParticleGun* fParticleGun;
    PrimaryGeneratorMessenger* fGunMessenger;
    
    TFile* fFile;
    TTree* fTree;
    
    // Input TTree content placeholders
    G4double fX0, fY0, fZ0;
    G4double **fX, **fY, **fE, **fArrivalTime;
    G4int **fIsSignal;
    G4int *fNumHits;
    G4bool fHasEventsCollection;
    G4int fEventsCollectionSize;
};

#endif
