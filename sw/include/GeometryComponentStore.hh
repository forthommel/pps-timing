#ifndef ComponentsMap_h
#define ComponentsMap_h

#include "GeometryComponent.hh"

#include <map>
#include <vector>
#include <string>

namespace PPS
{  
  class GeometryComponent;
  class GeometryComponentBuilder
  {
    public:
      virtual GeometryComponent* create(std::string)=0;
      std::string GetType() const { return ""; }
  };
  
  class GeometryComponentStore
  {
    private:
      GeometryComponentStore() { std::cout << __PRETTY_FUNCTION__ << std::endl;}
      static GeometryComponentStore* fComponentsStore;
      static bool fBuilt;

    public:
      typedef std::vector<std::string> Names;
      typedef std::map<std::string, GeometryComponentBuilder*> Map;
      typedef std::pair<std::string, GeometryComponentBuilder*> Pair;
      
      ~GeometryComponentStore() { fBuilt=false; }
      static GeometryComponentStore* GetInstance();
      
      void AddComponent(std::string,GeometryComponentBuilder*);
      
      inline size_t GetNumRegisteredComponents() const { return fMap.size(); }
      Names GetRegisteredComponents() const;
      GeometryComponentBuilder* GetByType(std::string);

    private:
      Map fMap;
  };
}

#endif
