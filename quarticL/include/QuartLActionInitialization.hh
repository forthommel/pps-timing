#ifndef QuartLActionInitialization_h
#define QuartLActionInitialization_h

#include "G4VUserActionInitialization.hh"

#include "QuartLPrimaryGeneratorAction.hh"
#include "QuartLRunAction.hh"
#include "QuartLEventAction.hh"
#include "QuartLStackingAction.hh"

class QuartLActionInitialization : public G4VUserActionInitialization
{
  public:
    QuartLActionInitialization();
    virtual ~QuartLActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
        
  private:
    G4VUserPrimaryGeneratorAction* fPrimaryGenerator;
    G4UserRunAction* fRunAction;
    G4UserEventAction* fEventAction;
    G4UserStackingAction* fStackingAction;
    QuartLAnalyzer *fAnalyzer;
};

#endif
