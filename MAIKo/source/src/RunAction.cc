
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
    G4int id;
    
    id = analysisManager->CreateH1("h1","Energy deposit in LG", 500, 0., 5.);
    analysisManager->SetH1Activation(id,true);
    analysisManager->SetH1Title(id, "Energy deposit in Lead-Glass");
    analysisManager->SetH1XAxisTitle(id, "Energy deposit (GeV)");
    analysisManager->SetH1YAxisTitle(id, "(count/10MeV)");
 // H2
    id = analysisManager->CreateH2("h2","Projection Energy vs Deposit Energy",500, 0., 5., 500, 0., 5.);
    analysisManager->SetH2Activation(id,true);
    analysisManager->SetH2Title(id,"Projection Energy vs Deposit Energy");
    analysisManager->SetH2XAxisTitle(id,"Projection Energy (GeV)");
    analysisManager->SetH2YAxisTitle(id,"Deposit Energy (GeV)");
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
  G4String fileName = "LeadGlass";
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
