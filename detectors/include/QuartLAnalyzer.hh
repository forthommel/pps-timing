#ifndef QuartLAnalyzer_h
#define QuartLAnalyzer_h

#include "G4Step.hh"

#include "QuartLInformation.h"

#include "TTree.h"
#include "TFile.h"
#include "TH2.h"

#define MAX_HITS 25000
#define MAX_MODULES 4

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
    /** \brief Fills all branches in the TTree for one given event */
    void FillTree();
    /** \brief Store the TTree onto an external ROOT file */
    void Store();
    inline G4int GetNumHitsInEvent() const { return fNumHits; }
  
  private:
    TFile *fFile;
    TTree *fTree;
    
    TString fFilename;
    
    TH2D *fHitMap[MAX_MODULES];
    TH2D *fEnergyMap[MAX_MODULES];
    
    /** \brief Total number of hits collected in one single event */
    G4int fNumHits;
    /** \brief Total number of events generated in all runs */
    G4int fNumEvents;
    G4int fRunId;
    
    G4double fVx[MAX_HITS];
    G4double fVy[MAX_HITS];
    G4double fVz[MAX_HITS];
    
    G4double fProductionTime[MAX_HITS];
    G4double fTrackLength[MAX_HITS];
    
    G4double fPx[MAX_HITS];
    G4double fPy[MAX_HITS];
    G4double fPz[MAX_HITS];
    G4double fE[MAX_HITS];
    
    G4int fStationId[MAX_HITS];
    G4int fCellId[MAX_HITS];
    
    PPS::QuartLInformation *fQuartLInfo;
};

#endif
