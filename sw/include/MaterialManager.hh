#ifndef MaterialManager_h
#define MaterialManager_h

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"

class MaterialManager
{
  public:
    MaterialManager();
    ~MaterialManager();
    
    G4Material* Air;
    G4Material* Sil;
    G4Material* Sapphire;
    G4Material* Glass;

    G4OpticalSurface* OpSilSurface;

  private:
    /** Generate and add material properties table */
    void BuildOpticalProperties();

    
};

#endif

