#include "MBP.hh"

using namespace CLHEP;

namespace MBP
{
  MBP::MBP(G4String name) :
    GeometryComponent(name),
    fParser(0)
  {
    fParser = new G4GDMLParser;
    fParser->Read("../data/MBP_v11.gdml");

    std::ostringstream cl; cl << GetName() << "_container_log";
    std::ostringstream cp; cp << GetName() << "_container_phys";
    G4Box* container_box = new G4Box("Container", 1.*m, 1.*m, 1.*m); // FIXME dimensions !
    G4LogicalVolume* container_log = new G4LogicalVolume(container_box, fContainerMaterial, cl.str(), 0, 0, 0);
    G4PVPlacement* container_phys = new G4PVPlacement(
      &fRotation,
      G4ThreeVector(
        fPosition.x(),
        fPosition.y(),
        fPosition.z()
      ),
      container_log,
      cp.str(),
      fParentLog,
      false,
      0
    );
    
    //fPhys = fParser->GetWorldVolume();
    G4cout << fParser->GetPosition("v1") << "\t" << G4endl;
    //fPhys->SetMotherLogical(fParentLog);
    //fPhys->SetTranslation(fPosition);
    //fPhys->SetRotation(&fRotation);

    fPhys = container_phys;
  }
  
  MBP::~MBP()
  {
    delete fParser;
  }
}
