#ifndef QuartLRunAction_h
#define QuartLRunAction_h

#include "globals.hh"
#include "G4UserRunAction.hh"

class G4Timer;
class G4Run;

class QuartLRunAction : public G4UserRunAction
{
  public:
    QuartLRunAction();
   ~QuartLRunAction();

  public:
    void BeginOfRunAction(const G4Run* aRun);
    void EndOfRunAction(const G4Run* aRun);

  private:
    G4Timer* timer;
};

#endif
