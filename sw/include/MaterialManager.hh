#ifndef MaterialManager_h
#define MaterialManager_h

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"

namespace PPS
{
  /**
   * \date Feb 2015
   * \author Laurent Forthomme <laurent.forthomme@cern.ch>
   */
  class MaterialManager
  {
    public:
      MaterialManager();
      ~MaterialManager();

      G4Material* Air;
      G4Material* SilO;
      G4Material* Silicon;
      G4Material* Sapphire;
      G4Material* Glass;
      G4Material* StainlessSteel;
      G4Material* AlBeMet;
      G4Material* Beryllium;

      G4OpticalSurface* OpSilSurface;

    private:
      /** Generate and add material properties table */
      void BuildOpticalProperties();
  };
}

#endif

