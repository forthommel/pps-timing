#ifndef QuartLStackingAction_h
#define QuartLStackingAction_h

#include "G4UserStackingAction.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

#include "globals.hh"

class QuartLStackingAction : public G4UserStackingAction
{
  public:
    QuartLStackingAction();
    ~QuartLStackingAction();
    
    /** \brief Method to be run on every new track in the iterative tracking. */
    G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    void NewStage();
    void PrepareNewEvent();

  private:
    G4int gammaCounter;
};

#endif
