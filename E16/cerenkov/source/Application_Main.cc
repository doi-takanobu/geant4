//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geant4 Application: Tutorial course for Hep/Medicine Users
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "UserActionInitialization.hh"
#include "PhysicsList.hh"
//#ifdef G4MULTITHREADED
//#include "G4MTRunManager.hh"
//#else
#include "G4RunManager.hh"
//#endif
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"

//-------------------------------------------------------------------------------
  int main( int argc, char** argv )
//-------------------------------------------------------------------------------
{
// Construct the default run manager
//#ifdef G4MULTITHREADED
//  G4MTRunManager* runManager = new G4MTRunManager;
//  runManager->SetNumberOfThreads(4);
//  G4cout << "Multithread Mode!!!!" << G4endl;
//#else
  G4RunManager* runManager = new G4RunManager;
  G4cout << "Normal Mode!!!!" << G4endl;
  //#endif

// Set up mandatory user initialization: Geometry
   runManager->SetUserInitialization( new Geometry );

// Set up mandatory user initialization: Physics-List
//   runManager->SetUserInitialization( new FTFP_BERT );
   runManager->SetUserInitialization(new PhysicsList);

// Set up user initialization: User Actions
   runManager->SetUserInitialization( new UserActionInitialization );

// Initialize G4 kernel
   runManager->Initialize();

// Create visualization environment
   G4VisManager* visManager = new G4VisExecutive;
   visManager->Initialize();

// Start interactive session
   G4UIExecutive* uiExec    = new G4UIExecutive(argc, argv);
   G4UImanager*   uiManager = G4UImanager::GetUIpointer();
   uiManager->ApplyCommand("/control/execute GlobalSetup.mac");
   uiExec->SessionStart();

// Job termination
   delete uiExec;
   delete visManager;
   delete runManager;

   return 0;
}
