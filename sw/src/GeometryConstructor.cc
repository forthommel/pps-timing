#include "GeometryConstructor.hh"

using namespace CLHEP;

namespace PPS
{
  GeometryConstructor::GeometryConstructor() :
    fWorld(0)
  {
    fMessenger = new GeometryConstructorMessenger(this);
    fMaterial = new MaterialManager;

    GeometryComponentStore::Names comp = GeometryComponentStore::GetInstance()->GetRegisteredComponents();
    G4cout << __PRETTY_FUNCTION__  << " : " << GeometryComponentStore::GetInstance()->GetNumRegisteredComponents() << " component(s) registered :"<< G4endl;
    for (GeometryComponentStore::Names::iterator it=comp.begin(); it!=comp.end(); it++) {
      G4cout << "--> \"" << *it << "\"" << G4endl;
    }
  }
  
  GeometryConstructor::~GeometryConstructor()
  {
    delete fMessenger;
    delete fMaterial;
    if (fWorld) delete fWorld;
  }
  
  G4VPhysicalVolume*
  GeometryConstructor::Construct()
  {
    // Build the detector geometry (along with the
    // sensitive detectors associated to it)
    //return ConstructGeometry();
    // Experimental hall
    G4Box* expHall_box = new G4Box("World_tmp", 1.*m/2., 1.*m/2., 1.*m/2.);     
    G4LogicalVolume* expHall_log = new G4LogicalVolume(expHall_box, fMaterial->Air, "World_tmp", 0, 0, 0);
    return new G4PVPlacement(0, G4ThreeVector(), expHall_log, "World_tmp", 0, false, 0);
  }
  
  G4VPhysicalVolume*
  GeometryConstructor::ConstructGeometry()
  {
    // First clean old geometry, if any
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    RunAction* run = (RunAction*)G4RunManager::GetRunManager()->GetUserRunAction();
    // Then unlock the output file to allow the addition of
    // events placeholders from our sensitive detectors
    run->GetFileWriter()->GetEventInformation()->UnLock();
    
    // Build a (sensitive) experimental hall
    fWorld = new BoundingBox("World");
    fWorld->SetSDname("World");
    fWorld->BeforeConstruct();
    G4cout << "fworld successfully built" << G4endl;
    
    // Build all the components added by user's macro
    G4int i = 0;
    for (ComponentsRef::iterator det=fComponents.begin(); det!=fComponents.end(); det++, i++) {
      G4cout << __PRETTY_FUNCTION__ << " building detector " << i << " at " << fComponentsLocation[i] << G4endl;
      (*det)->SetParent(fWorld);
      (*det)->SetCenter(fComponentsLocation.at(i));
      (*det)->BeforeConstruct();
      (*det)->Construct();
      fComponentsBuilt.at(i) = true;
    }
    
    // Finally lock the output file to avoid the addition of
    // events placeholders from additional sensitive detectors
    run->GetFileWriter()->GetEventInformation()->Lock();

    return fWorld->GetPhysicalVolume();
  }

  G4int
  GeometryConstructor::AddNewComponent(G4String type)
  {
    std::ostringstream ss; ss << type << "_" << fComponents.size();
    GeometryComponent* comp = GeometryComponentStore::GetInstance()->GetByType(type)->Build(ss.str());
    if (!comp) return -1;
    
    fComponents.push_back(static_cast<GeometryComponent*>(comp));
    // By default the component is set to the origin
    fComponentsLocation.push_back(G4ThreeVector());
    fComponentsBuilt.push_back(false);
    
    return fComponents.size()-1;
  }
  
  G4bool
  GeometryConstructor::MoveComponent(G4int id, G4ThreeVector pos)
  {
    if ((id<0) or ((size_t)id>=fComponentsLocation.size())) return false;
    fComponentsLocation.at(id) = pos;
    return true;
  }
  
  G4bool
  GeometryConstructor::RotateComponentTheta(G4int id, G4double theta)
  {
    if ((id<0) or ((size_t)id>=fComponentsLocation.size())) return false;
    fComponents.at(id)->RotateTheta(theta);
    return true;
  }
  
  G4bool
  GeometryConstructor::RotateComponentPhi(G4int id, G4double phi)
  {
    if ((id<0) or ((size_t)id>=fComponentsLocation.size())) return false;
    fComponents.at(id)->RotatePhi(phi);
    G4cout << __PRETTY_FUNCTION__ << " -> " << phi << G4endl;
    return true;
  }
  
  G4bool
  GeometryConstructor::SetSDname(G4int id, G4String name)
  {
    if ((id<0) or ((size_t)id>=fComponentsLocation.size())) return false;
    fComponents.at(id)->SetSDname(name);
    return true;
  }
  
  void
  GeometryConstructor::UpdateGeometry()
  {
    G4cout << __PRETTY_FUNCTION__ << " ====> Geometry update !" << G4endl;
    G4RunManager::GetRunManager()->DefineWorldVolume(ConstructGeometry());
    G4SDManager::GetSDMpointer()->AddNewDetector(fWorld->GetSensitiveDetector());
  }
  
  void
  GeometryConstructor::WriteGDML(G4String filename)
  {
    G4GDMLParser parser;
    parser.Write(filename, fWorld->GetPhysicalVolume(), true, "gdml/gdml.xsd");
  }
}
