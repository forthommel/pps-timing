#ifndef QuartLRunAction_h
#define QuartLRunAction_h

#include "globals.hh"
#include "G4UserRunAction.hh"

#include "QuartLAnalyzer.hh"

class G4Timer;
class G4Run;

class QuartLRunAction : public G4UserRunAction
{
  public:
    QuartLRunAction(QuartLAnalyzer* analyzer=0);
   ~QuartLRunAction();

    void BeginOfRunAction(const G4Run* aRun);
    void EndOfRunAction(const G4Run* aRun);
    inline QuartLAnalyzer* GetAnalyzer() { return fAnalyzer; }

  private:
    G4Timer* fTimer;
    QuartLAnalyzer *fAnalyzer;
};

#endif
