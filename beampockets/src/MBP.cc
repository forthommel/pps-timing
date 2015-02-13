#include "MBP.hh"

MBP::MBP(G4String name, window_type window_material, G4bool only_window) :
  Component(name),
  fParser(0)
{
  fParser = new G4GDMLParser;
  /*switch (window_material_) {
    case ALBEMET: case BERYLLIUM: case STAINLESS_STEEL: default:
      fParser->Read("../data/MBP_v11.gdml");
      break;
      }*/
  fParser->Read("../data/MBP_v11.gdml");
  
  fPhys = fParser->GetWorldVolume();
  G4cout << fParser->GetPosition("v1") << "\t" << G4endl;
  fPhys->SetTranslation(fPosition);
  fPhys->SetMotherLogical(fParentLog);
}

MBP::~MBP()
{
  delete fParser;
}
