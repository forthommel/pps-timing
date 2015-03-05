#include "MBP.hh"

namespace MBP
{
  MBP::MBP(G4String name) :
    GeometryComponent(name),
    fParser(0)
  {
    fParser = new G4GDMLParser;
    fParser->Read("../data/MBP_v11.gdml");
    
    fPhys = fParser->GetWorldVolume();
    G4cout << fParser->GetPosition("v1") << "\t" << G4endl;
    //fPhys->SetMotherLogical(fParentLog);
    //fPhys->SetTranslation(fPosition);
    //fPhys->SetRotation(&fRotation);
  }
  
  MBP::~MBP()
  {
    delete fParser;
  }
}
