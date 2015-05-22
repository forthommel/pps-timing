#ifndef GeometryConstructorMessenger_h
#define GeometryConstructorMessenger_h

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "globals.hh"

#include "GeometryConstructor.hh"

namespace PPS
{
  class GeometryConstructor; // Forward declaration by construction
  /**
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class GeometryConstructorMessenger : public G4UImessenger
  {
    public:
      GeometryConstructorMessenger(GeometryConstructor*);
      ~GeometryConstructorMessenger();

      void SetNewValue(G4UIcommand*, G4String);

  private:
    GeometryConstructor *fDC;

    G4UIdirectory* fPPSDir;
    G4UIcmdWithAString* fAddComponent;
    G4UIcmdWith3VectorAndUnit* fComponentPosition;
    G4UIcmdWithADoubleAndUnit* fComponentRotationTheta;
    G4UIcmdWithADoubleAndUnit* fComponentRotationPhi;
    G4UIcmdWithAString* fComponentSDname;
    G4UIcmdWithoutParameter* fUpdateGeometry;
    G4UIcmdWithAString* fGDMLOutput;
    G4UIcmdWithAString* fGDMLLoad;

    G4int fLastComponentAdded;
  };
}

#endif
