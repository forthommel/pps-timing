#ifndef QuartLPrimaryGeneratorMessenger_h
#define QuartLPrimaryGeneratorMessenger_h

#include "G4UImessenger.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"

#include "globals.hh"

#include "QuartLPrimaryGeneratorAction.hh"

class QuartLPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

class QuartLPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    QuartLPrimaryGeneratorMessenger(QuartLPrimaryGeneratorAction*);
   ~QuartLPrimaryGeneratorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    QuartLPrimaryGeneratorAction* fAction;
    G4UIcmdWithADoubleAndUnit* fPolarCmd;
    G4UIcmdWithAString* fInputFilename;
    G4UIcmdWith3Vector* fProbeCell;
};

#endif
