
#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4UnitsTable.hh"
#include "Analysis.hh"
#include "Randomize.hh"
#include <iomanip>


EventAction::EventAction()
 : G4UserEventAction() 
{}


EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
    for(G4int i=0; i<noSi+noNaI+noGAGG;i++){
        sum_eDep[i] = 0.;
    }
}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //G4double sum_Si = 0.;
    if(GetSum(1)==0&&GetSum(2)==0)return;
    for(G4int i=0; i<noSi; i++){
        //G4cout << "sum_eDep["<<i+1000 << "] = "<< GetSum(i)<<G4endl;
	//sum_Si += GetSum(i);
        analysisManager->FillH1(i, GetSum(i));   //H1 id = 0 ~ 12
	analysisManager->FillH2(0,GetSum(i),GetSum(1));
	analysisManager->FillH2(1,GetSum(i),GetSum(2));
    }
    analysisManager->FillH1(1,GetSum(1));
    analysisManager->FillH1(2,GetSum(2));
    analysisManager->FillH2(2,GetSum(0),GetSum(0)+GetSum(1)+GetSum(2));
        //sum_BGO = sum_BGO + GetSum(i);
    //G4cout << "全てのBGOでのエネルギー付与 : "<< sum_BGO <<G4endl;
    //analysisManager->FillH1(21, sum_BGO);

    G4cout << "Siのエネルギー: " << GetSum(0) << "MeV" << G4endl;
    G4cout << "NaIのエネルギー: " << GetSum(1) << "MeV" << G4endl;
    G4cout << "GAGGのエネルギー: " << GetSum(2) << "MeV" << G4endl;
}

