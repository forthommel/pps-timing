#include "QuartLDetectorConstruction.hh"

using namespace CLHEP;

QuartLDetectorConstruction::QuartLDetectorConstruction()
{
//  expHall_x = expHall_y = expHall_z = 1*m;

  expHall_x = 300*mm;		//was 120
  expHall_y = 300*mm;		//was 120
  expHall_z = 300*mm;  		//was 100 
 
  bar_x    =   3*mm;		//From Mike, 
  bar_y    =   3*mm;
 
  barh_l   =  40*mm;		// 

  barv_l   =  20*mm;		// was 40, 5.03.2014
    
  wind_x    = 2*mm;
  wind_y    = 3*mm;
  wind_z    = 3*mm;
}

// 

QuartLDetectorConstruction::~QuartLDetectorConstruction(){;}

// 

void
QuartLDetectorConstruction::BuildOpticalProperties()
{
  G4NistManager* man = G4NistManager::Instance();

  Air = man->FindOrBuildMaterial("G4_AIR");  
  Sil = man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  //was Sil = man->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");   //Sapphire
  Glass = man->FindOrBuildMaterial("G4_GLASS_PLATE");
    
  //
  // Optical properties for air
  //
  const G4int nEntries_Air = 10;
  
  G4double PhEn_Air[nEntries_Air] =	// Photon energies
    {
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
  
  //
  // Optical properties for Quartz (SiO2) 
  //
  const G4int nEntries_Sil = 10;

  G4double PhEn_Sil[nEntries_Sil] =	// Photon energies
    {
      1.76*eV, 1.96*eV, 2.27*eV, 2.44*eV, 2.65*eV,
      3.06*eV, 3.71*eV, 4.50*eV, 5.19*eV, 5.79*eV
    };  
  
  G4double RI_Sil[nEntries_Sil] =
    {
      1.455, 1.457, 1.460, 1.462, 1.464,
      1.470, 1.480, 1.496, 1.513, 1.534
    }; 
 
  G4double Absor_Sil[nEntries_Sil];
  for (G4int i=0; i<nEntries_Sil; i++) {
    Absor_Sil[i] = 0.5*m;
  }
  
  //
  //	Sapphire (Al2O3) Part
  //
  /*----------------------------------------------------
    const G4int nEntries = 13; 
    G4double PhEn[nEntries] =			//Photon Energy
            { 2.10*eV, 
	      2.32*eV, 2.40*eV, 2.53*eV, 2.80*eV,
	      3.53*eV, 3.81*eV, 4.02*eV, 4.42*eV,
	      4.82*eV, 5.08*eV, 5.48*eV, 5.82*eV
	      };
    G4double RI_Sil[nEntries] =
            { 1.768, 1.771, 1.773, 1.775, 1.797, 1.780, 1.805,
	      1.811, 1.824, 1.840, 1.851, 1.870, 1.890 
	      }; 
 
       
    G4double Absor_Sil[nEntries] =
           { 0.5*m,  0.5*m,   0.5*m,    0.5*m, 
	     0.5*m,  0.5*m,   0.5*m,    0.5*m,
	     0.47*m, 0.45*m,  0.42*m,   0.40*m, 0.37*m	     
	      };
    ------------------------------------------------------*/
  //
  
  G4MaterialPropertiesTable* MPT_Sil = new G4MaterialPropertiesTable();
  MPT_Sil->AddProperty("RINDEX", PhEn_Sil, RI_Sil, nEntries_Sil);
  MPT_Sil->AddProperty("ABSLENGTH", PhEn_Sil, Absor_Sil, nEntries_Sil);
  
  Sil->SetMaterialPropertiesTable(MPT_Sil);
  
  //
  // Optical properties for PMT's window glass
  //
  const G4int nEntries_Gl = 10;
  
  G4double PhEn_Gl[nEntries_Gl] =	// Photon energies
    {
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
  
  //
  //  Optical Properties of the Surface 
  //
  G4double sigma_alpha = 0.1;			//0.1
  
  OpSilSurface = new G4OpticalSurface("SiOSurface");
  
  OpSilSurface->SetType(dielectric_dielectric);
  OpSilSurface->SetFinish(polished);
  //  OpSilSurface->SetModel(glisur);
  OpSilSurface->SetModel(unified);  
  OpSilSurface->SetSigmaAlpha(sigma_alpha);
  
  //
  // Material Properties Table attached to the optical surfaces
  //
  const G4int nEntries_OP = 2;
  
  G4double PhEn_OP[nEntries_OP] = {1.76*eV, 5.79*eV};  //Si02
  
  //  G4double PhEn_OP[nEntries_OP] = {2.10*eV, 5.82*eV};    //Al2O3
  
  // Optical SiO2/Al2O3 Surface
  G4double RefractiveIndex[nEntries_OP] = {1.455, 1.534}; //  SiO2
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

G4VPhysicalVolume*
QuartLDetectorConstruction::Construct()
{
  
  BuildOpticalProperties();
  
  //
  //	------------- Volumes  and Detector --------------
  //
  // The experimental Hall
  //
  G4Box* expHall_box = new G4Box("World",expHall_x,expHall_y,expHall_z);
  
  G4LogicalVolume* expHall_log = new G4LogicalVolume(
    expHall_box,
    Air,
    "World",
    0,0,0);
  
  G4VPhysicalVolume* expHall_phys = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);
  
  //
  // BAR: The L Bar, 22.01.2012, 14.01.2015
  //	
  
  const G4int nBar = 40; 
  
  G4double RadL[nBar] = {
    // First Station
    18*mm, 23*mm, 18*mm, 23*mm,
    28*mm, 33*mm, 28*mm, 33*mm,
    38*mm, 43*mm, 38*mm, 43*mm,
    48*mm, 53*mm, 48*mm, 53*mm,
    58*mm, 63*mm, 58*mm, 63*mm,             
    // Second Station
    18*mm, 23*mm, 18*mm, 23*mm,
    28*mm, 33*mm, 28*mm, 33*mm,
    38*mm, 43*mm, 38*mm, 43*mm,
    48*mm, 53*mm, 48*mm, 53*mm,
    58*mm, 63*mm, 58*mm, 63*mm       
  };
			    
  G4double LigL[nBar] =  {
    // First Station
    58.80*mm, 58.80*mm, 58.80*mm, 58.80*mm,
    61.90*mm, 61.90*mm, 61.90*mm, 61.90*mm,
    65.00*mm, 65.00*mm, 65.00*mm, 65.00*mm,
    68.10*mm, 68.10*mm, 68.10*mm, 68.10*mm,
    71.20*mm, 71.20*mm, 71.20*mm, 71.20*mm,
    // Second Station
    58.80*mm, 58.80*mm, 58.80*mm, 58.80*mm,
    61.90*mm, 61.90*mm, 61.90*mm, 61.90*mm,
    65.00*mm, 65.00*mm, 65.00*mm, 65.00*mm,
    68.10*mm, 68.10*mm, 68.10*mm, 68.10*mm,
    71.20*mm, 71.20*mm, 71.20*mm, 71.20*mm
  };
			     			      
  G4double Yoffs[nBar] = {
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm, 
    
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm  
  };			      
  
  G4double Xoffs[nBar] = { 
    4.7*mm,  4.7*mm,  4.7*mm,  4.7*mm,
    1.6*mm,  1.6*mm,  1.6*mm,  1.6*mm,
    -1.5*mm, -1.5*mm, -1.5*mm, -1.5*mm,
    -4.6*mm, -4.6*mm, -4.6*mm, -4.6*mm,
    -7.7*mm, -7.7*mm, -7.7*mm, -7.7*mm,
    
    4.7*mm,  4.7*mm,  4.7*mm,  4.7*mm,
    1.6*mm,  1.6*mm,  1.6*mm,  1.6*mm,
    -1.5*mm, -1.5*mm, -1.5*mm, -1.5*mm,
    -4.6*mm, -4.6*mm, -4.6*mm, -4.6*mm,
    -7.7*mm, -7.7*mm, -7.7*mm, -7.7*mm
  }; 		      		 			      			      
  
  G4double Zoffs[nBar] = { // Z adjustment
    0.*mm,  2.5*mm,  0.*mm,  2.5*mm,
    5.*mm,  7.5*mm,  5.*mm,  7.5*mm,
    10.*mm, 12.5*mm, 10.*mm, 12.5*mm,
    15.*mm, 17.5*mm, 15.*mm, 17.5*mm,
    20.*mm, 22.5*mm, 20.*mm, 22.5*mm,
    //Shift between First and Second Station 
    70.*mm,  72.5*mm,  70.*mm,  72.5*mm,	
    75.*mm,  77.5*mm,  75.*mm,  77.5*mm,
    80.*mm,  82.5*mm,  80.*mm,  82.5*mm,
    85.*mm,  87.5*mm,  85.*mm,  87.5*mm,
    90.*mm,  92.5*mm,  90.*mm,  92.5*mm			
  };			    

  G4Box*             BarV[nBar];
  G4Box*             BarH[nBar];
  G4UnionSolid*      Bar[nBar];
  G4LogicalVolume*   Bar_log[nBar];
  G4VPhysicalVolume* Bar_phys[nBar];
  
  //G4ThreeVector      Trans;
  G4ThreeVector      Cellsh;		//Physical Volumes shifting
  G4ThreeVector      Windsh;		//For Window shifting
  
  G4Box* window_box = new G4Box("Window",wind_x/2., wind_z/2., wind_z/2.);    
  G4LogicalVolume*   window_log[nBar]; 
  G4VPhysicalVolume* window_phys[nBar];
  
  DetectorSD* windowSD = new DetectorSD("DetectorSD"); 
  G4SDManager* sdMan = G4SDManager::GetSDMpointer();
  sdMan->AddNewDetector(windowSD);      
  
  for (int i=0; i < nBar; i++) {
    
    barv_l = RadL[i];
    barh_l = LigL[i];
    
    BarV[i] = new G4Box("BarV",bar_x/2.,bar_y/2., barv_l/2.);	//Vertical Bar (Radiator)
    
    BarH[i] = new G4Box("BarH",barh_l/2.,bar_y/2., bar_x/2.);	//Horizontal Bar (LightG)
    //
    //	Logical OR, Passive Method
    //
    
    G4ThreeVector Trans(barh_l/2.+bar_x/2., 0., barv_l/2.-bar_x/2.);  
    
    Bar[i] = new G4UnionSolid("BarV+BarH", BarV[i], BarH[i], 0, Trans);
    
    Bar_log[i] = new G4LogicalVolume(Bar[i],  Sil ,"Bar",0,0,0);
    
    
    Bar_phys[i] = new G4PVPlacement(0, G4ThreeVector(Xoffs[i], Yoffs[i], Zoffs[i]), Bar_log[i], "Bar", expHall_log, false, i ); 
    //			
    //------------------------------------------------------------
    //	Glass Window of Sensitive Detector
    //
    
    window_log[i] = new G4LogicalVolume(window_box, Glass,"Window",0,0,0);
    window_log[i]->SetSensitiveDetector(windowSD);
    
    window_phys[i] = new G4PVPlacement(0, G4ThreeVector(barh_l+bar_x/2.+wind_x/2.+Xoffs[i], Yoffs[i], barv_l/2.-wind_z/2.+Zoffs[i]), window_log[i], "Window", expHall_log, false, i);
    
  }
  
  
  G4LogicalBorderSurface* SilAirBord[nBar];
  G4LogicalBorderSurface* PMSilSurf[nBar];

  //
  //	Bar-Air Border
  //
  for (int i=0; i<nBar; i++) {
    SilAirBord[i] = new G4LogicalBorderSurface("SilAirBord", Bar_phys[i], expHall_phys, OpSilSurface);    
  }   
  
  //
  //	Bar-PM Window Surface
  //
    for (int i=0; i<nBar; i++) {
    PMSilSurf[i] = new G4LogicalBorderSurface("PMSilBord", Bar_phys[i], window_phys[i], OpSilSurface);      //  PMSilSurf
  }
  
  return expHall_phys;
}

// 
