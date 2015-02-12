#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "G4ios.hh"

//#include "LHEP.hh" //FIXME
#include "QGSP_BERT.hh"
#include "LBE.hh"

#include "G4OpticalPhysics.hh"
#include "G4VModularPhysicsList.hh"

#include "globals.hh"

#include "SteppingVerbose.hh"
#include "ActionInitialization.hh"
#include "GeometryConstructor.hh"

#include "QuartLDetectorConstruction.hh"

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

int main(int argc,char** argv)
{
  // Seed the random number generator manually
  //
  G4long myseed = 345354;
  CLHEP::HepRandom::setTheSeed(myseed);

  // User Verbose output class
  //
  G4VSteppingVerbose* verbosity = new SteppingVerbose;
  G4VSteppingVerbose::SetInstance(verbosity);

  // Run manager
  //
/*#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif*/
  G4RunManager* runManager = new G4RunManager;

  // UserInitialization classes - mandatory
  //
  //QuartLDetectorConstruction* detector = new QuartLDetectorConstruction;
  //runManager->SetUserInitialization(detector);
  //
  GeometryConstructor *geom_constructor = new GeometryConstructor;
  runManager->SetUserInitialization(geom_constructor);
  
  G4VModularPhysicsList* physics;

  //physics = new QuartLPhysicsList;
  //physics = new LHEP;    //22.01 from AK
  //physics = new QGSP_BERT(-1);
  physics = new LBE;
  physics->SetVerboseLevel(-1);
  physics->RegisterPhysics(new G4OpticalPhysics);

  runManager-> SetUserInitialization(physics);

  ActionInitialization* action = new ActionInitialization;
  runManager->SetUserInitialization(action);

  // Initialize G4 kernel
  //
  runManager->Initialize();

  /*for (G4int i=0; i<20; i++) {
    const G4ThreeVector cell_center = detector->GetCellCenter(1, i);
    G4cout << "--> Cell center for id = " << i << " -> (" << cell_center.x() << ", " << cell_center.y() << ", " << cell_center.z() << ")" << G4endl;
  }*/

  // Get the pointer to the User Interface manager
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (argc==1) { // Define UI session for interactive mode
    G4UIExecutive* ui;
    ui = new G4UIExecutive(argc, argv);
    // Initialize visualization
#ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
#endif
    UImanager->ApplyCommand("/control/execute test/vis.mac");
    ui->SessionStart();
#ifdef G4VIS_USE
  delete visManager;
#endif
  }
  else { // Batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
#ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
#endif
    UImanager->ApplyCommand(command+fileName);
#ifdef G4VIS_USE
    delete visManager;
#endif
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

    delete runManager;
    delete verbosity;

    return 0;
}
