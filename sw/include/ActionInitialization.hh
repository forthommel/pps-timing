#ifndef ActionInitialization_h
#define ActionInitialization_h

#include "G4VUserActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "StackingAction.hh"

#include "QuartLAnalyzer.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
        
  private:
    G4VUserPrimaryGeneratorAction* fPrimaryGenerator;
    G4UserEventAction* fEventAction;
    G4UserStackingAction* fStackingAction;
    QuartLAnalyzer *fAnalyzer;
};

#endif
