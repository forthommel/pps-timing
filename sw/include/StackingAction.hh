#ifndef StackingAction_h
#define StackingAction_h

#include "G4UserStackingAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "globals.hh"

namespace PPS
{
  /**
   * \brief User-defined class to classify tracks (so far, unused...)
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class StackingAction : public G4UserStackingAction
  {
    public:
      StackingAction();
      ~StackingAction();
    
      /** \brief Method to be run on every new track in the iterative tracking. */
      G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
      void NewStage();
      void PrepareNewEvent();

    private:
  };
}

#endif
