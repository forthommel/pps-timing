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
  return ConstructGeometry();
}

G4VPhysicalVolume*
GeometryConstructor::ConstructGeometry()
{
  // Clean old geometry, if any
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  
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

  G4cout << __PRETTY_FUNCTION__ << G4endl;

  G4int i=0;
  for (DetectorsRef::iterator det=fDetectors.begin(); det!=fDetectors.end(); det++) {
    G4cout << __PRETTY_FUNCTION__ << " building detector " << i << " at " << fDetectorsLocation[i] << G4endl;
    (*det)->Construct();
    i++;
  }
  
  return expHall_phys;
}

G4int
GeometryConstructor::AddNewComponent(G4String type)
{
  G4cout << __PRETTY_FUNCTION__ << " --> Let's add a \"" << type << "\", shall we ?" << G4endl;
  if (type=="QUARTIC") {
    fDetectors.push_back((G4VUserDetectorConstruction*)(new QuartLDetectorConstruction));
    fDetectorsLocation.push_back(G4ThreeVector());
  }
  return fDetectors.size()-1;
}

G4bool
GeometryConstructor::MoveComponent(G4int id, G4ThreeVector pos)
{
  if (id<0) return false;
  if ((size_t)id>=fDetectorsLocation.size()) return false;
  fDetectorsLocation[id] = pos;
  return true;
}

void
GeometryConstructor::UpdateGeometry()
{
  G4cout << __PRETTY_FUNCTION__ << " ====> Geometry update !" << G4endl;
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructGeometry());
}
