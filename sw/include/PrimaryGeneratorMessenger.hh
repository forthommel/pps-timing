#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "globals.hh"

#include "PrimaryGeneratorAction.hh"

namespace PPS
{
  class PrimaryGeneratorAction;
  /**
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class PrimaryGeneratorMessenger : public G4UImessenger
  {
    public:
      PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
      ~PrimaryGeneratorMessenger();

      void SetNewValue(G4UIcommand*, G4String);

    private:
      PrimaryGeneratorAction* fAction;
      G4UIcmdWithADoubleAndUnit* fPolarCmd;
      G4UIcmdWithAString* fInputFilename;
      G4UIcmdWith3Vector* fProbeCell;
  };
}

#endif
