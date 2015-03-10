#include "MaterialManager.hh"

using namespace CLHEP;

namespace PPS
{
  MaterialManager::MaterialManager() :
    Air(0), SilO(0), Silicon(0), Sapphire(0), Glass(0),
    StainlessSteel(0), AlBeMet(0), Beryllium(0),
    OpSilSurface(0)
  {
    G4NistManager* man = G4NistManager::Instance();
    
    Air = man->FindOrBuildMaterial("G4_AIR");
    SilO = man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    Silicon = man->FindOrBuildMaterial("G4_Si");
    Sapphire = man->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
    Glass = man->FindOrBuildMaterial("G4_GLASS_PLATE");
    StainlessSteel = man->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    Beryllium = man->FindOrBuildMaterial("G4_Be");
    
    // Properties inherited from CMS values (Geometry/CMSCommonData/data/materials.xml)
    AlBeMet = new G4Material("AlBeMet", 2.071*g/cm3, 4);
    AlBeMet->AddElement(man->FindOrBuildElement("Al"), 0.38);
    AlBeMet->AddElement(man->FindOrBuildElement("Be"), 0.615);
    AlBeMet->AddElement(man->FindOrBuildElement("C"), 0.0005);
    AlBeMet->AddElement(man->FindOrBuildElement("O"), 0.0045);
    
    BuildOpticalProperties();
  }
  
  MaterialManager::~MaterialManager()
  {}
  
  void
  MaterialManager::BuildOpticalProperties()
  {
    // Optical properties for air
    
    const G4int nEntries_Air = 10;
    
    G4double PhEn_Air[nEntries_Air] = { // Photon energies
      1.76*eV, 1.96*eV, 2.27*eV, 2.44*eV, 2.65*eV,
      3.06*eV, 3.71*eV, 4.50*eV, 5.19*eV, 5.79*eV
    };
    G4double RI_Air[nEntries_Air];
    for (G4int i=0; i<nEntries_Air; i++) {
      RI_Air[i] = 1.00;
    }
    
    G4MaterialPropertiesTable* MPT_Air = new G4MaterialPropertiesTable();
    MPT_Air->AddProperty("RINDEX", PhEn_Air, RI_Air, nEntries_Air);
    Air->SetMaterialPropertiesTable(MPT_Air);
    
    // Optical properties for Quartz (SiO2)
    
    const G4int nEntries_Sil = 10;
    
    G4double PhEn_Sil[nEntries_Sil] = { // Photon energies
      1.76*eV, 1.96*eV, 2.27*eV, 2.44*eV, 2.65*eV,
      3.06*eV, 3.71*eV, 4.50*eV, 5.19*eV, 5.79*eV
    };
    G4double RI_Sil[nEntries_Sil] = {
      1.455, 1.457, 1.460, 1.462, 1.464,
      1.470, 1.480, 1.496, 1.513, 1.534
    };
    G4double Absor_Sil[nEntries_Sil];
    for (G4int i=0; i<nEntries_Sil; i++) {
      Absor_Sil[i] = 0.5*m;
    }
    
    G4MaterialPropertiesTable* MPT_Sil = new G4MaterialPropertiesTable();
    MPT_Sil->AddProperty("RINDEX", PhEn_Sil, RI_Sil, nEntries_Sil);
    MPT_Sil->AddProperty("ABSLENGTH", PhEn_Sil, Absor_Sil, nEntries_Sil);
    SilO->SetMaterialPropertiesTable(MPT_Sil);
    
    // Sapphire (Al2O3) Part
    
    const G4int nEntries_Sap = 13;
    
    G4double PhEn_Sap[nEntries_Sap] = { // Photon energies
      2.10*eV, 2.32*eV, 2.40*eV, 2.53*eV,
      2.80*eV, 3.53*eV, 3.81*eV, 4.02*eV,
      4.42*eV, 4.82*eV, 5.08*eV, 5.48*eV,
      5.82*eV
    };
    G4double RI_Sap[nEntries_Sap] = {
      1.768, 1.771, 1.773, 1.775,
      1.797, 1.780, 1.805, 1.811,
      1.824, 1.840, 1.851, 1.870,
      1.890
    };
    G4double Absor_Sap[nEntries_Sap] = {
      0.50*m, 0.50*m, 0.50*m, 0.50*m,
      0.50*m, 0.50*m, 0.50*m, 0.50*m,
      0.47*m, 0.45*m, 0.42*m, 0.40*m,
      0.37*m
    };
    
    G4MaterialPropertiesTable* MPT_Sap = new G4MaterialPropertiesTable();
    MPT_Sap->AddProperty("RINDEX", PhEn_Sap, RI_Sap, nEntries_Sap);
    MPT_Sap->AddProperty("ABSLENGTH", PhEn_Sap, Absor_Sap, nEntries_Sap);
    Sapphire->SetMaterialPropertiesTable(MPT_Sap);
    
    // QUARTIC PMT's window glass
    
    const G4int nEntries_Gl = 10;
    
    G4double PhEn_Gl[nEntries_Gl] = { // Photon energies
      1.76*eV, 1.96*eV, 2.27*eV, 2.44*eV, 2.65*eV,
      3.06*eV, 3.71*eV, 4.50*eV, 5.19*eV, 5.79*eV
    };
    G4double RI_Gl[nEntries_Gl];
    G4double Absor_Gl[nEntries_Gl];
    for (G4int i=0; i<nEntries_Gl; i++) {
      RI_Gl[i] = 1.70;
      Absor_Gl[i] = 1.*m;
    }
    
    G4MaterialPropertiesTable* MPT_Gl = new G4MaterialPropertiesTable();
    MPT_Gl->AddProperty("RINDEX", PhEn_Gl, RI_Gl, nEntries_Gl);
    MPT_Gl->AddProperty("ABSLENGTH", PhEn_Gl, Absor_Gl, nEntries_Gl);
    Glass->SetMaterialPropertiesTable(MPT_Gl);
    
    // Optical Properties of the Surfaces
    
    G4double sigma_alpha = 0.1;
    
    OpSilSurface = new G4OpticalSurface("SiOSurface");
    
    OpSilSurface->SetType(dielectric_dielectric);
    OpSilSurface->SetFinish(polished);
    //OpSilSurface->SetModel(glisur);
    OpSilSurface->SetModel(unified);
    OpSilSurface->SetSigmaAlpha(sigma_alpha);
    
    // Material Properties Table attached to the optical surfaces
    
    const G4int nEntries_OP = 2;
    
    G4double PhEn_OP[nEntries_OP] = {1.76*eV, 5.79*eV};  // Si02
    //G4double PhEn_OP[nEntries_OP] = {2.10*eV, 5.82*eV}; //Al2O3
    
    // Optical SiO2/Al2O3 Surface
    G4double RefractiveIndex[nEntries_OP] = {1.455, 1.534}; // SiO2
    G4double SpecularLobe[nEntries_OP] = {0.1, 0.1};
    G4double SpecularSpike[nEntries_OP] = {0.9, 0.9};
    G4double Backscatter[nEntries_OP] = {0.0, 0.0};
    G4double QualSurfaceRefl[nEntries_OP] = {0.99, 0.99};
    
    G4MaterialPropertiesTable* ST_Sur = new G4MaterialPropertiesTable();
    ST_Sur->AddProperty("RINDEX", PhEn_OP, RefractiveIndex, nEntries_OP);
    ST_Sur->AddProperty("REFLECTIVITY", PhEn_OP, QualSurfaceRefl, nEntries_OP);
    ST_Sur->AddProperty("SPECULARLOBECONSTANT", PhEn_OP, SpecularLobe, nEntries_OP);
    ST_Sur->AddProperty("SPECULARSPIKECONSTANT", PhEn_OP, SpecularSpike, nEntries_OP);
    ST_Sur->AddProperty("BACKSCATTERCONSTANT", PhEn_OP, Backscatter, nEntries_OP);
    OpSilSurface->SetMaterialPropertiesTable(ST_Sur);
  }
}
