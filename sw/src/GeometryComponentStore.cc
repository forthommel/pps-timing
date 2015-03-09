#include "GeometryComponentStore.hh"

namespace PPS
{  
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
