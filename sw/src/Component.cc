#include "Component.hh"

Component::Component(G4String name) :
  fName(name),
  fParentLog(0), fParentPhys(0), fPhys(0),
  fIsSensitive(false), fSDname("")
{
  fMaterial = ((RunAction*)G4RunManager::GetRunManager()->GetUserRunAction())->GetMaterialManager();
}

Component::~Component()
{}

G4VPhysicalVolume*
Component::Construct()
{
  G4cout << __PRETTY_FUNCTION__ << " Building a new component with name \"" << fName << "\"" << G4endl;
  if (fIsSensitive && fSDname!="") {
    fSD = new DetectorSD(fSDname);
    G4SDManager* sd_manager = G4SDManager::GetSDMpointer();
    sd_manager->AddNewDetector(fSD);
  }
  return fPhys;
}
