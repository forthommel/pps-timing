#include "GeometryComponent.hh"

namespace PPS
{
  GeometryComponent::GeometryComponent(G4String name) :
    fName(name), fMaterial(((const RunAction*)G4RunManager::GetRunManager()->GetUserRunAction())->GetMaterialManager()),
    fParentLog(0), fParentPhys(0), fPhys(0), fLog(0), fContainerMaterial(fMaterial->Air),
    fIsSensitive(false), fSDname(""), fEvent(0)
  {}
  
  GeometryComponent::~GeometryComponent()
  {}
  
  G4VPhysicalVolume*
  GeometryComponent::Construct()
  {
    G4cout << __PRETTY_FUNCTION__ << " Building a new component with name \"" << fName << "\"" << G4endl;
    return fPhys;
  }
  
  //////////////////////////////////////////////////////////////////////////////
  
  bool GeometryComponentStore::fBuilt = false;
  GeometryComponentStore* GeometryComponentStore::fComponentsStore = 0;
  
  GeometryComponentStore*
  GeometryComponentStore::GetInstance()
  {
    if (!fBuilt) {
      fComponentsStore = new GeometryComponentStore;
      fBuilt = true;
      return fComponentsStore;
    }
    return fComponentsStore;
  }
  
  void
  GeometryComponentStore::AddComponent(std::string type, GeometryComponentBuilder* comp)
  {
    fMap.insert(Pair(type, comp));
  }
  
  std::vector<std::string>
  GeometryComponentStore::GetRegisteredComponents() const
  {
    Names out;
    for (Map::const_iterator it=fMap.begin(); it!=fMap.end(); it++) {
      out.push_back(it->first);
    }
    return out;
  }
  
  GeometryComponentBuilder*
  GeometryComponentStore::GetByType(std::string type)
  {
    for (Map::iterator it=fMap.begin(); it!=fMap.end(); it++) {
      if (it->first==type) return it->second;
    }
    return 0;
  }
}
