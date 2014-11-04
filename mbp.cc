#include "G4GDMLParser.hh"
#include "MBPDetectorConstruction.hh"
#include "MBPActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
//#include "QBBC.hh"
#include "QGSP_BERT.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  const G4bool fShowEventDisplay = true;
  MBPAnalysis *analysis;
  MBPActionInitialization *action;
  G4VModularPhysicsList* physicsList;
  //MBPDetectorConstruction *detector;
  G4VUserDetectorConstruction *detector;
  G4UIExecutive* ui;
  G4GDMLParser parser;
  window_type wt;
  G4String wtstr;
  TString filename;
  G4double xpos;
  G4int num_protons, seed;
  G4double window_length_from, window_length_to;
  G4int window_length_scan_num;

  num_protons = seed = -1;

  // Choose the Random engine
  //
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  //
//#ifdef G4MULTITHREADED
//  G4MTRunManager* runManager = new G4MTRunManager;
//#else
  G4RunManager* runManager = new G4RunManager;
//#endif

  // Set mandatory initialization classes
  //

  // Detector construction
  wt = STAINLESS_STEEL;
  parser.Read("../data/MBP_v09.gdml");
  if (seed>=0) G4Random::setTheSeed(seed, 4);
  
  // User action initialization
  detector = new MBPDetectorConstruction(parser.GetWorldVolume());
  runManager->SetUserInitialization(detector);
    
  // Physics list
  //physicsList = new QBBC;
  physicsList = new QGSP_BERT;
  physicsList->SetVerboseLevel(0);
  runManager->SetUserInitialization(physicsList);

  analysis = new MBPAnalysis(filename.Data());
  analysis->SetStoreRootFile(false);
  action = new MBPActionInitialization(analysis);
  runManager->SetUserInitialization(action);
  
  // Initialize G4 kernel
  //
  runManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

#ifdef G4VIS_USE
  if (fShowEventDisplay) {
    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
  }
#endif

#ifdef G4UI_USE
  if (fShowEventDisplay) ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
  if (fShowEventDisplay) UImanager->ApplyCommand("/control/execute init_vis.mac");
#endif
#endif

  action->GetPrimaryGenerator()->SetGenerationPosition(G4ThreeVector(0., 0., -999.));
  
  /*UImanager->ApplyCommand("/run/reinitializeGeometry");  
    detector->UpdateGeometry();*/
  //UImanager->ApplyCommand(ss.str().c_str());
  //G4cout << " --> " << (G4double)analysis->GetNumTracksInRun()/num_protons << " tracks"  << G4endl;
  //out <<  length/mm << "\t" << (G4double)analysis->GetNumTracksInRun()/num_protons << "\t" << (G4double)analysis->GetTotalEnergyLossInRun(true)/num_protons << G4endl;
  //out.close();

  if (fShowEventDisplay) {
    ui->SessionStart();
    delete ui;
  }
  
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
/*#ifdef G4VIS_USE
  delete visManager;
#endif*/
  delete analysis;
  delete runManager; // FIXME

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
