#ifndef QuartLPrimaryGeneratorMessenger_h
#define QuartLPrimaryGeneratorMessenger_h

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
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
    G4UIdirectory* gunDir; 
    G4UIcmdWithADoubleAndUnit* polarCmd;
    G4UIcmdWithAString* fInputFilename;
};

#endif
