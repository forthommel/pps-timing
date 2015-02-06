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

#include "G4OpticalPhysics.hh"
#include "G4VModularPhysicsList.hh"

#include "globals.hh"

#include "QuartLDetectorConstruction.hh"
#include "QuartLSteppingVerbose.hh"
#include "QuartLActionInitialization.hh"

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
  G4VSteppingVerbose* verbosity = new QuartLSteppingVerbose;
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
  G4VUserDetectorConstruction* detector = new QuartLDetectorConstruction;
  runManager-> SetUserInitialization(detector);
  //

  G4VModularPhysicsList* physics;

  //physics = new QuartLPhysicsList;
  //physics = new LHEP;    //22.01 from AK
  physics = new QGSP_BERT;
  physics->RegisterPhysics(new G4OpticalPhysics);

  runManager-> SetUserInitialization(physics);

  QuartLActionInitialization* action = new QuartLActionInitialization;
  runManager->SetUserInitialization(action);

  // Initialize G4 kernel
  //
  runManager->Initialize();

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
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
#ifdef G4VIS_USE
  delete visManager;
#endif
  }
  else { // Batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

  delete runManager;
  delete verbosity;

  return 0;
}
