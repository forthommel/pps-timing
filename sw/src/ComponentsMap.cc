#include "ComponentsMap.hh"

namespace PPS
{
  bool ComponentsStore::fBuilt = false;
  ComponentsStore* ComponentsStore::fComponentsStore = 0;
  
  ComponentsStore* ComponentsStore::GetInstance()
  {
    if (!fBuilt) {
      fComponentsStore = new ComponentsStore;
      fBuilt = true;
      return fComponentsStore;
    }
    return fComponentsStore;
  }
}
