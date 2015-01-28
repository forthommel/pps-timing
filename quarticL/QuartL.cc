//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh" 

#include "G4ios.hh"

#include "LHEP.hh"
#include "G4OpticalPhysics.hh"

#include "QuartLDetectorConstruction.hh"

// #include "QuartLPhysicsList.hh"

#include "QuartLPrimaryGeneratorAction.hh"
#include "QuartLRunAction.hh"
#include "QuartLEventAction.hh"
#include "QuartLStackingAction.hh"
#include "QuartLSteppingVerbose.hh"

#include "Randomize.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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
  G4RunManager* runManager = new G4RunManager;

  // UserInitialization classes - mandatory
  //
  G4VUserDetectorConstruction* detector = new QuartLDetectorConstruction;
  runManager-> SetUserInitialization(detector);
  //
  
  
  
//  G4VUserPhysicsList* physics = new QuartLPhysicsList;

  G4VModularPhysicsList* physics = new LHEP;		//22.01 from AK
  physics->RegisterPhysics(new G4OpticalPhysics);

  runManager-> SetUserInitialization(physics);
  
  
  
#ifdef G4VIS_USE
  // visualization manager
  //
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  // UserAction classes
  //
  G4UserRunAction* run_action = new QuartLRunAction;
  runManager->SetUserAction(run_action);
  //
  G4VUserPrimaryGeneratorAction* gen_action = new QuartLPrimaryGeneratorAction;
  runManager->SetUserAction(gen_action);
  //
  G4UserEventAction* event_action = new QuartLEventAction;
  runManager->SetUserAction(event_action);
  //
  G4UserStackingAction* stacking_action = new QuartLStackingAction;
  runManager->SetUserAction(stacking_action);
  
  // Initialize G4 kernel
  //
  runManager->Initialize();
    
  // Get the pointer to the User Interface manager
  //
  G4UImanager* UI = G4UImanager::GetUIpointer(); 
   
  if (argc==1)   // Define UI session for interactive mode
    {
      G4UIsession* session = 0;
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);      
#else
      session = new G4UIterminal();
#endif    
#ifdef G4VIS_USE
      UI->ApplyCommand("/control/execute vis.mac");     
#endif
      session->SessionStart();
      delete session;
   }
   
  else         // Batch mode
   {
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);
   }
   
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;
  delete verbosity;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
