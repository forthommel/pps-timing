#ifndef QuartLAnalyzer_h
#define QuartLAnalyzer_h

#include "TTree.h"
#include "G4Step.hh"

#define MAX_HITS 25000

class QuartLAnalyzer
{
  public:
    QuartLAnalyzer(G4String filename="events.root");
    ~QuartLAnalyzer();
    
    void AddHitInEvent(G4Step* step);
    void Store();
  
  private:
    G4String fFilename;
    TTree *fTree;
    
    G4int fNumHits;
    
    G4double fVx[MAX_HITS];
    G4double fVy[MAX_HITS];
    G4double fVz[MAX_HITS];
    
    G4double fPx[MAX_HITS];
    G4double fPy[MAX_HITS];
    G4double fPz[MAX_HITS];
    G4double fE[MAX_HITS];
    
    G4int fCellId[MAX_HITS];
};

#endif
