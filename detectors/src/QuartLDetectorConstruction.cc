#include "QuartLDetectorConstruction.hh"

using namespace CLHEP;

const G4int nBar = 20;

const G4double fYoffs[nBar] = {
  -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
  -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
  -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
  -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm,
  -4.7*mm, -1.6*mm, 1.5*mm, 4.6*mm
};

const G4double fXoffs[nBar] = {
   4.7*mm,  4.7*mm,  4.7*mm,  4.7*mm,
   1.6*mm,  1.6*mm,  1.6*mm,  1.6*mm,
  -1.5*mm, -1.5*mm, -1.5*mm, -1.5*mm,
  -4.6*mm, -4.6*mm, -4.6*mm, -4.6*mm,
  -7.7*mm, -7.7*mm, -7.7*mm, -7.7*mm
};

const G4double fZoffs[nBar] = {
  0.*mm,  2.5*mm,  0.*mm,  2.5*mm,
  5.*mm,  7.5*mm,  5.*mm,  7.5*mm,
  10.*mm, 12.5*mm, 10.*mm, 12.5*mm,
  15.*mm, 17.5*mm, 15.*mm, 17.5*mm,
  20.*mm, 22.5*mm, 20.*mm, 22.5*mm
};

QuartLDetectorConstruction::QuartLDetectorConstruction() :
  fNumBars(0), fNumStations(0)
{
//  expHall_x = expHall_y = expHall_z = 1*m;

  expHall_x = 300*mm;		// was 120
  expHall_y = 300*mm;		// was 120
  expHall_z = 300*mm;  	// was 100

  bar_x    =   3*mm;		// From Mike
  bar_y    =   3*mm;

  barh_l   =  40*mm;		//

  barv_l   =  20*mm;		// was 40, 5.03.2014

  wind_x    = 2*mm;
  wind_y    = 3*mm;
  wind_z    = 3*mm;

  fMaterial = new MaterialManager;
}

QuartLDetectorConstruction::~QuartLDetectorConstruction(){
  delete fMaterial;
}

G4VPhysicalVolume*
QuartLDetectorConstruction::Construct()
{
  // ------------- Volumes  and Detector --------------
  //
  // experimental Hall
  //
  G4Box* expHall_box = new G4Box("World", expHall_x, expHall_y, expHall_z);

  windowSD = new DetectorSD("DetectorSD");
  G4SDManager* sdMan = G4SDManager::GetSDMpointer();
  sdMan->AddNewDetector(windowSD);

  expHall_log = new G4LogicalVolume(
    expHall_box,
    fMaterial->Air,
    "World",
    0, 0, 0);

  expHall_phys = new G4PVPlacement(0, G4ThreeVector(), expHall_log, "World", 0, false, 0);

  BuildOneStation(G4ThreeVector(0., 0., 0.));
  BuildOneStation(G4ThreeVector(0., 0., 70.*mm));
  /*BuildOneStation(G4ThreeVector(0., 0., 140.*mm));
  BuildOneStation(G4ThreeVector(0., 0., 210.*mm));*/

  return expHall_phys;
}

void
QuartLDetectorConstruction::BuildOneStation(G4ThreeVector pos)
{
  //
  // BAR: The L Bar, 22.01.2012, 14.01.2015
  //
  fStationPosition[fNumStations] = pos;

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

  G4Box* window_box = new G4Box("Window", wind_x/2., wind_z/2., wind_z/2.);

  for (G4int i=0; i<nBar; i++) {
    if (fNumBars>MAX_BARS) {
      std::ostringstream ss;
      ss << "Too many cells to be constructed !" << G4endl
         << "  Maximal number of stations : " << MAX_BARS;
      G4Exception("QuartLDetectorConstruction::BuildOneStation", "TooManyCells", FatalException, ss);
    }

    barv_l = RadL[i];
    barh_l = LigL[i];

    BarV[fNumBars] = new G4Box("BarV", bar_x/2., bar_y/2., barv_l/2.); // Vertical Bar (Radiator)
    BarH[fNumBars] = new G4Box("BarH", barh_l/2., bar_y/2., bar_x/2.); // Horizontal Bar (LightG)
    //
    // Logical OR, Passive Method
    //

    G4ThreeVector Trans(barh_l/2.+bar_x/2., 0., barv_l/2.-bar_x/2.);

    std::ostringstream ss;
    ss << "Bar_" << fNumStations << "_" << i;

    Bar[fNumBars] = new G4UnionSolid("BarV+BarH", BarV[fNumBars], BarH[fNumBars], 0, Trans);
    Bar_log[fNumBars] = new G4LogicalVolume(Bar[fNumBars], fMaterial->Sil, ss.str(), 0, 0, 0);
    //Bar_log[fNumBars] = new G4LogicalVolume(Bar[fNumBars], fMaterial->Sapphire, ss.str(), 0, 0, 0);
    Bar_phys[fNumBars] = new G4PVPlacement(
      0,
      G4ThreeVector(fXoffs[i]+pos.x(), fYoffs[i]+pos.y(), fZoffs[i]+pos.z()),
      Bar_log[fNumBars],
      ss.str(),
      expHall_log,
      false,
      fNumBars);
    //
    //------------------------------------------------------------
    // Glass Window of Sensitive Detector
    //

    window_log[fNumBars] = new G4LogicalVolume(window_box, fMaterial->Glass, "Window", 0, 0, 0);
    window_log[fNumBars]->SetSensitiveDetector(windowSD);

    window_phys[fNumBars] = new G4PVPlacement(
      0,
      G4ThreeVector(
        fXoffs[i]+fStationPosition[fNumStations].x()+wind_x/2.+barh_l+bar_x/2.,
        fYoffs[i]+fStationPosition[fNumStations].y(),
        fZoffs[i]+fStationPosition[fNumStations].z()-wind_z/2.+barv_l/2.
      ),
      window_log[fNumBars],
      "Window",
      expHall_log,
      false,
      fNumBars);

    // Bar-Air Border
    SilAirBord[fNumBars] = new G4LogicalBorderSurface("SilAirBord", Bar_phys[i], expHall_phys, fMaterial->OpSilSurface);
    // Bar-PM Window Surface
    PMSilSurf[fNumBars] = new G4LogicalBorderSurface("PMSilBord", Bar_phys[i], window_phys[i], fMaterial->OpSilSurface); // PMSilSurf

    fNumBars += 1;
  }
  fNumStations += 1;
}

G4ThreeVector
QuartLDetectorConstruction::GetCellCenter(G4int station_id, G4int cell_id) const
{
  G4double x, y, z;
  x = fStationPosition[station_id].x()+fXoffs[cell_id-cell_id%4];
  y = fStationPosition[station_id].y()+fYoffs[cell_id%4];
  z = fStationPosition[station_id].z();
  return G4ThreeVector(x, y, z);
}
