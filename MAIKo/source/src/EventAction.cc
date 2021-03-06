
#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4UnitsTable.hh"
#include "Analysis.hh"
#include "Randomize.hh"
#include <iomanip>
#include "G4SystemOfUnits.hh"

EventAction::EventAction()
 : G4UserEventAction() 
{}


EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
    for(G4int i=0; i<noLG;i++){
        sum_eDep[i] = 0.;
    }
}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //G4double sum_Si = 0.;
    for(G4int i=0; i<noLG; i++){
        //G4cout << "sum_eDep["<<i+1000 << "] = "<< GetSum(i)<<G4endl;
	//sum_Si += GetSum(i);
     //H1
        analysisManager->FillH1(i, GetSum(i)/GeV);
	analysisManager->FillH2(i, BEAM_ENERGY/GeV, GetSum(i)/GeV);
    }
        //sum_BGO = sum_BGO + GetSum(i);
    //G4cout << "全てのBGOでのエネルギー付与 : "<< sum_BGO <<G4endl;
    //analysisManager->FillH1(21, sum_BGO);

}

