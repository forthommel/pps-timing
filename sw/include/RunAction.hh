#ifndef RunAction_h
#define RunAction_h

#include "globals.hh"
#include "G4UserRunAction.hh"

#include "QuartLAnalyzer.hh"

#include "TFile.h"
#include "TTree.h"

class G4Timer;
class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction(QuartLAnalyzer* analyzer=0);
    ~RunAction();

    void BeginOfRunAction(const G4Run* aRun);
    void EndOfRunAction(const G4Run* aRun);
    /** \brief Returns a pointer to the QuartLAnalyzer object used to collect all tracks' information in an external ROOT tree */
    inline QuartLAnalyzer* GetAnalyzer() { return fAnalyzer; }

  private:
    G4Timer* fTimer;
    QuartLAnalyzer *fAnalyzer;
};

#endif
