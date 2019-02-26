
#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "EventAction.hh"


RunAction::RunAction()
 : G4UserRunAction()
{
    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    // G4cout << "Using " << analysisManager->GetType() << G4endl;
    analysisManager->SetActivation(true);

    // Create directories
    //analysisManager->SetHistoDirectoryName("histograms");
    //analysisManager->SetNtupleDirectoryName("ntuple");
    analysisManager->SetVerboseLevel(1);
    //analysisManager->SetFirstHistoId(1);
    //analysisManager->SetFileName("telescope");
    //analysisManager->SetHistoDirectoryName("histo");
    // Book histograms, ntuple
    //
    
    // Creating histograms
//H1
    G4String hist_Name[3] =
      {"h1_Si","h1_NaI","h1_GAGG"};
    G4int id;
    G4String temp;
    G4int max;
    for(G4int i=0;i<3;i++){
      switch(i){
      case 0:
	temp = "Si";
	max = 50.;
	break;
      case 1:
	temp = "NaI";
	max = 100.;
	break;
      case 2:
	temp = "GAGG";
	max = 100.;
	break;
      default:
	break;
      }
      id = analysisManager->CreateH1(hist_Name[i],temp, 400, 0., max*MeV);
      analysisManager->SetH1Activation(id,true);
    }
 // H2
    id = analysisManager->CreateH2("h2_NaI","NaI vs SiAll", 300, 0, 60.*MeV, 200,  0., 50.*MeV);
    analysisManager->SetH2Activation(id,true);
    id = analysisManager->CreateH2("h2_GAGG","GAGG vs SiAll", 300, 0, 60.*MeV, 200,  0., 50.*MeV);
    analysisManager->SetH2Activation(id,true);
    id = analysisManager->CreateH2("EdE","E vs dE", 300, 0, 60.*MeV, 200,  0., 100.*MeV);
    analysisManager->SetH2Activation(id,true);
 
}



RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}



void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
    
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  // G4String fileName = "Pixel";
  G4String fileName = "telescope";
  analysisManager->OpenFile(fileName);
    //G4cout << "File " << fileName << " Open" <<G4endl;
    
}



void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();


}
