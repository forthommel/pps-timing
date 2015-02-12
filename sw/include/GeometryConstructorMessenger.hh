#ifndef GeometryConstructorMessenger_h
#define GeometryConstructorMessenger_h

#include "G4UImessenger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3Vector.hh"
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
    G4UIcmdWithAString *fAddComponent;
    G4UIcmdWith3Vector *fComponentPosition;

    G4int fLastComponentAdded;
    
};

#endif
