#ifndef ActionInitialization_h
#define ActionInitialization_h

#include "G4VUserActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "StackingAction.hh"
#include "TrackingAction.hh"
#include "FileWriter.hh"

#include "ComponentsMap.hh"

namespace PPS
{
  /**
   * Object holding all user information to be filled and propagated by Geant4 along the simulation stage
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class ActionInitialization : public G4VUserActionInitialization
  {
    public:
      ActionInitialization();
      virtual ~ActionInitialization();

      virtual void BuildForMaster() const;
      virtual void Build() const;

    private:
      G4UserEventAction* fEventAction;
      G4VUserPrimaryGeneratorAction* fPrimaryGenerator;
      G4UserStackingAction* fStackingAction;
      G4UserTrackingAction* fTrackingAction;
      FileWriter* fOutput;
  };
}

#endif
