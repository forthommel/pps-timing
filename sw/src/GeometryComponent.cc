#include "GeometryComponent.hh"

namespace PPS
{
  GeometryComponent::GeometryComponent(G4String name) :
    fName(name),
    fParentLog(0), fParentPhys(0), fPhys(0),
    fIsSensitive(false), fSDname(""), fEvent(0)
  {
    fMaterial = ((RunAction*)G4RunManager::GetRunManager()->GetUserRunAction())->GetMaterialManager();
    fContainerMaterial = fMaterial->Air;
  }
  
  GeometryComponent::~GeometryComponent()
  {}
  
  G4VPhysicalVolume*
  GeometryComponent::Construct()
  {
    G4cout << __PRETTY_FUNCTION__ << " Building a new component with name \"" << fName << "\"" << G4endl;
    return fPhys;
  }
}
