#include "MBP.hh"

using namespace CLHEP;

namespace MBP
{
  MBP::MBP(G4String name) :
    PPS::GeometryComponent(name),
    fParser(0)
  {}
  
  G4VPhysicalVolume*
  MBP::BuildOneStation()
  {
    G4Box* container_box = new G4Box("Container", 1.*m, 1.*m, 1.*m); // FIXME dimensions !
    G4LogicalVolume* container_log = new G4LogicalVolume(container_box, fContainerMaterial, GetLogName(), 0, 0, 0);
    G4PVPlacement* container_phys = new G4PVPlacement(
      &fRotation,
      G4ThreeVector(
        fPosition.x(),
        fPosition.y(),
        fPosition.z()
      ),
      container_log,
      GetPhysName(),
      fParentLog,
      false,
      0
    );
    
    fParser = new G4GDMLParser;
    fParser->Read("../data/MBP_v11.gdml");
    
    G4VPhysicalVolume* mbp_phys = fParser->GetWorldVolume();
    //G4cout << fParser->GetPosition("v1") << "\t" << G4endl;
    mbp_phys->SetMotherLogical(fParentLog);
    mbp_phys->SetTranslation(fPosition);
    mbp_phys->SetRotation(&fRotation);

    return container_phys;

    //PPS::ComponentsMap::GetComponentsMap()->AddComponent(this);

  }
  
  MBP::~MBP()
  {
    if (fParser) delete fParser;
  }

  REGISTER_COMPONENT(MBP, "MBP")
}
