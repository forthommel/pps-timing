#include "QuartLDetector.hh"

using namespace CLHEP;

namespace Quartic
{
  const G4int nBar = 20;
  
  const G4double fXoffs[nBar] = {
    4.7*mm,  4.7*mm,  4.7*mm,  4.7*mm,
    1.6*mm,  1.6*mm,  1.6*mm,  1.6*mm,
    -1.5*mm, -1.5*mm, -1.5*mm, -1.5*mm,
    -4.6*mm, -4.6*mm, -4.6*mm, -4.6*mm,
    -7.7*mm, -7.7*mm, -7.7*mm, -7.7*mm
  };
  
  const G4double fYoffs[nBar] = {
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
    -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm
  };
  
  const G4double fZoffs[nBar] = {
    0.*mm,  2.5*mm,  0.*mm,  2.5*mm,
    5.*mm,  7.5*mm,  5.*mm,  7.5*mm,
    10.*mm, 12.5*mm, 10.*mm, 12.5*mm,
    15.*mm, 17.5*mm, 15.*mm, 17.5*mm,
    20.*mm, 22.5*mm, 20.*mm, 22.5*mm
  };
  
  QuartLDetector::QuartLDetector(G4String name) :
    PPS::GeometryComponent(name),
    fSD(0), fNumBars(0),
    fContainerMaterial(fMaterial->Air)
  {
    G4cout << __PRETTY_FUNCTION__ << " New detector with name \"" << fName << "\" created" << G4endl;
    bar_x    =   3*mm;		// From Mike
    bar_y    =   3*mm;
    
    barh_l   =  40*mm;		//
    
    barv_l   =  20*mm;		// was 40, 5.03.2014
    
    wind_x    = 2*mm;
    wind_y    = 3*mm;
    wind_z    = 3*mm;
  }
  
  QuartLDetector::~QuartLDetector()
  {}
  
  void
  QuartLDetector::BeforeConstruct()
  {
    // ------------- Volumes  and Detector --------------
    fSD = new QuartLDetectorSD(fSDname);
    G4SDManager* sd_manager = G4SDManager::GetSDMpointer();
    sd_manager->AddNewDetector(fSD);
    fPhys = BuildOneStation();
  }
  
  G4VPhysicalVolume*
  QuartLDetector::BuildOneStation()
  {
    G4double Xoffs[nBar], Yoffs[nBar], Zoffs[nBar];
    //
    // BAR: The L Bar, 22.01.2012, 14.01.2015
    //
    G4double RadL[nBar] = {
      18*mm, 23*mm, 18*mm, 23*mm,
      28*mm, 33*mm, 28*mm, 33*mm,
      38*mm, 43*mm, 38*mm, 43*mm,
      48*mm, 53*mm, 48*mm, 53*mm,
      58*mm, 63*mm, 58*mm, 63*mm
    };
    
    G4double LigL[nBar] =  {
      58.80*mm, 58.80*mm, 58.80*mm, 58.80*mm,
      61.90*mm, 61.90*mm, 61.90*mm, 61.90*mm,
      65.00*mm, 65.00*mm, 65.00*mm, 65.00*mm,
      68.10*mm, 68.10*mm, 68.10*mm, 68.10*mm,
      71.20*mm, 71.20*mm, 71.20*mm, 71.20*mm
    };
    
    G4ThreeVector Cellsh; // Physical Volumes shifting
    G4ThreeVector Windsh; // For Window shifting
    
    G4double xlength = 5.*bar_x+LigL[0]+wind_x;
    G4double ylength = 4.*bar_y; //FIXME
    G4double zlength = RadL[nBar-1];
    
    for (size_t i=0; i<nBar; i++) {
      Xoffs[i] = -xlength/2.+fXoffs[i]+7.7*mm;
      Yoffs[i] = -ylength/2.+fYoffs[i]+4.7*mm;
      Zoffs[i] = -zlength/2.+fZoffs[i]+RadL[0]/2.;
    }
    
    G4Box* container_box = new G4Box("Container", xlength/2., ylength/2., zlength/2.);
    G4LogicalVolume* container_log = new G4LogicalVolume(container_box, fContainerMaterial, GetLogName(), 0, 0, 0);
    G4PVPlacement* container_phys = new G4PVPlacement(
      &fRotation,
      G4ThreeVector(
        fPosition.x()+xlength/2.,
        fPosition.y(),
        fPosition.z()+zlength/2.
      ),
      container_log,
      GetPhysName(),
      fParentLog,
      false,
      0
    );
    
    G4Box* window_box = new G4Box("Window", wind_x/2., wind_z/2., wind_z/2.);
    
    for (G4int i=0; i<nBar; i++) {      
      barv_l = RadL[i];
      barh_l = LigL[i];
      
      BarV[fNumBars] = new G4Box("BarV", bar_x/2., bar_y/2., barv_l/2.); // Vertical Bar (Radiator)
      BarH[fNumBars] = new G4Box("BarH", barh_l/2., bar_y/2., bar_x/2.); // Horizontal Bar (LightG)
      
      G4ThreeVector Trans(barh_l/2.+bar_x/2., 0., barv_l/2.-bar_x/2.);
      
      std::ostringstream ss;
      ss << "Bar_" << i;
      
      Bar[fNumBars] = new G4UnionSolid("BarV+BarH", BarV[fNumBars], BarH[fNumBars], 0, Trans);
      Bar_log[fNumBars] = new G4LogicalVolume(Bar[fNumBars], fMaterial->SilO, ss.str(), 0, 0, 0);
      //Bar_log[fNumBars] = new G4LogicalVolume(Bar[fNumBars], fMaterial->Sapphire, ss.str(), 0, 0, 0);
      Bar_phys[fNumBars] = new G4PVPlacement(
        0,
        G4ThreeVector(
          Xoffs[i],
          Yoffs[i],
          Zoffs[i]
        ),
        Bar_log[fNumBars],
        ss.str(),
        container_log,
        false,
        fNumBars);
      //
      //------------------------------------------------------------
      // Glass Window of Sensitive Detector
      //
      
      window_log[fNumBars] = new G4LogicalVolume(window_box, fMaterial->Glass, "Window", 0, 0, 0);
      window_log[fNumBars]->SetSensitiveDetector(fSD);
      
      window_phys[fNumBars] = new G4PVPlacement(
        0,
        G4ThreeVector(
          wind_x/2.+barh_l+bar_x/2.,
          0.,
         -wind_z/2.+barv_l/2.
        ),
        window_log[fNumBars],
        "Window",
        Bar_log[fNumBars],
        false,
        fNumBars);
      
      // Bar-Air Border
      SilAirBord[fNumBars] = new G4LogicalBorderSurface("SilAirBord", Bar_phys[i], fParentPhys, fMaterial->OpSilSurface);
      // Bar-PM Window Surface
      PMSilSurf[fNumBars] = new G4LogicalBorderSurface("PMSilBord", Bar_phys[i], window_phys[i], fMaterial->OpSilSurface); // PMSilSurf
      
      fNumBars += 1;
    }  
    return container_phys;
  }
  
  G4ThreeVector
  QuartLDetector::GetCellCenter(G4int cell_id) const
  {
    G4double x, y, z;
    x = fPosition.x()+fXoffs[cell_id-cell_id%4];
    y = fPosition.y()+fYoffs[cell_id%4];
    z = fPosition.z();
    return G4ThreeVector(x, y, z);
  }
  REGISTER_COMPONENT(QuartLDetector, "QUARTIC")
}
