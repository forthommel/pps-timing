#ifndef ComponentsMap_h
#define ComponentsMap_h

#include <map>
#include <string>

#include "GeometryComponent.hh"

//#define PPS::ComponentsMap<> gMBP;


/*  class ComponentsMap
  {
    private:
      ComponentsMap();
      static ComponentsMap* fComponentsMap;
      static bool fBuilt;

    public:
      ~ComponentsMap();
      static ComponentsMap* GetComponentsMap();
      
      inline void AddComponent(GeometryComponent* comp) {
        if (!fMap) return;
        fMap->insert(std::pair<std::string,GeometryComponent*>(comp->GetType(), comp));
      }
      
    private:
      std::map<std::string,GeometryComponent*>* fMap;
  };
  
  bool ComponentsMap::fBuilt = false;
  
  ComponentsMap* ComponentsMap::fComponentsMap = 0;
  ComponentsMap* ComponentsMap::GetComponentsMap()
  {
    if (!fBuilt) {
      fComponentsMap = new ComponentsMap;
      fBuilt = true;
      return fComponentsMap;
    }
    return fComponentsMap;
  }
  ComponentsMap::ComponentsMap()
  {
    fMap = new std::map<std::string,GeometryComponent*>;
  }
  ComponentsMap::~ComponentsMap()
  {
    fBuilt = false;
    delete fMap;
  }
}
*/

namespace PPS
{
  class ComponentsStore
  {
    private:
      ComponentsStore() {;}
      static ComponentsStore* fComponentsStore;
      static bool fBuilt;
      
    public:
      ~ComponentsStore() { fBuilt=false; }
      static ComponentsStore* GetInstance();
      inline void AddComponent(GeometryComponent* comp) {
        fMap.insert(std::pair<std::string, GeometryComponent*>(comp->GetType(), comp));
      }
      inline size_t GetNumRegisteredComponents() const { return fMap.size(); }
      inline std::vector<std::string> GetRegisteredComponents() const {
        std::vector<std::string> out;
        for (std::map<std::string, GeometryComponent*>::const_iterator it=fMap.begin(); it!=fMap.end(); it++) {
          out.push_back(it->first);
        }
        return out;
      }
      
    private:
      std::map<std::string, GeometryComponent*> fMap;
  };
  
  template <class T> class GeometryComponentProxy
  {
    public:
      GeometryComponentProxy() { 
        //fComponent = new T("");
        //ComponentsStore::GetInstance()->AddComponent(new T(""));
        ComponentsStore::GetInstance()->AddComponent((T*)NULL);
      }
      //GeometryComponent* CreateComponent() const { return new T(""); }
      virtual std::string GetType() const { return T::GetType(); }
      //virtual T* GetComponent() { return fComponent; }
    private:
      //T* fComponent;
  };
}

#endif
