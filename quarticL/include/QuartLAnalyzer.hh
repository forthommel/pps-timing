#ifndef QuartLAnalyzer_h
#define QuartLAnalyzer_h

#include "TTree.h"
#include "G4Step.hh"

#define MAX_HITS 25000

/** Analysis class intended to store into a TTree the photons kinematic information for each event. */
class QuartLAnalyzer
{
  public:
    /**
     * \brief Default class constructor to book the TTree and its different leaves to store the information.
     * \param[in] filename The file name to store the output tree.
     */
    QuartLAnalyzer(G4String filename="events.root");
    ~QuartLAnalyzer();
    
    /**
     * \brief Add a new photon hit on the PMT in the events' collection.
     * \param[in] step The Geant4 iterative step from which the photon kinematics is extracted.
     */
    void AddHitInEvent(G4Step* step);
    /** \brief Store the TTree onto an external ROOT file */
    void Store();
  
  private:
    G4String fFilename;
    TTree *fTree;
    
    G4int fNumHits;
    
    G4double fVx[MAX_HITS];
    G4double fVy[MAX_HITS];
    G4double fVz[MAX_HITS];
    
    G4double fProductionTime[MAX_HITS];
    
    G4double fPx[MAX_HITS];
    G4double fPy[MAX_HITS];
    G4double fPz[MAX_HITS];
    G4double fE[MAX_HITS];
    
    G4int fStationId[MAX_HITS];
    G4int fCellId[MAX_HITS];
    
};

#endif
