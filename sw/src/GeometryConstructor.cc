#include "GeometryConstructor.hh"

using namespace CLHEP;

GeometryConstructor::GeometryConstructor()
{
//  expHall_x = expHall_y = expHall_z = 1*m;
  expHall_x = 300*mm; // was 120
  expHall_y = 300*mm; // was 120
  expHall_z = 300*mm; // was 100

  fMessenger = new GeometryConstructorMessenger(this);
  fMaterial = new MaterialManager;
}

GeometryConstructor::~GeometryConstructor()
{
  delete fMessenger;
  delete fMaterial;
}

G4VPhysicalVolume*
GeometryConstructor::Construct()
{
  // Experimental hall
  G4Box* expHall_box = new G4Box("World", expHall_x, expHall_y, expHall_z);
  /*G4SDManager* sdMan = G4SDManager::GetSDMpointer();
  sdMan->AddNewDetector(windowSD);*/

  expHall_log = new G4LogicalVolume(
    expHall_box,
    fMaterial->Air,
    "World",
    0, 0, 0);

  expHall_phys = new G4PVPlacement(0, G4ThreeVector(), expHall_log, "World", 0, false, 0);

  return expHall_phys;
}

