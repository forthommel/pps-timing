#ifndef GeometryConstructorMessenger_h
#define GeometryConstructorMessenger_h

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "globals.hh"

#include "GeometryConstructor.hh"

class GeometryConstructor;

class GeometryConstructorMessenger : public G4UImessenger
{
  public:
    GeometryConstructorMessenger(GeometryConstructor*);
    ~GeometryConstructorMessenger();

    void SetNewValue(G4UIcommand*, G4String);

  private:
    GeometryConstructor *fDC;

    G4UIdirectory* fPPSDir;
    G4UIcmdWithAString *fAddComponent;
    G4UIcmdWith3VectorAndUnit *fComponentPosition;
    G4UIcmdWithAString *fComponentSDname;
    G4UIcmdWithoutParameter* fUpdateGeometry;

    G4int fLastComponentAdded;
    
};

#endif
