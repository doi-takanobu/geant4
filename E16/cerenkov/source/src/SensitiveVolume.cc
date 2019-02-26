//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SensitiveVolume.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "SensitiveVolume.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4HCofThisEvent.hh"
#include "G4RunManager.hh"
#include "Analysis.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
G4int doistep = 0;

//------------------------------------------------------------------------------
  SensitiveVolume::SensitiveVolume(G4String name)
  : G4VSensitiveDetector(name)
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  SensitiveVolume::~SensitiveVolume()
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  void SensitiveVolume::Initialize(G4HCofThisEvent*)
//------------------------------------------------------------------------------
{
    sum_eDep_Si = 0.;
    sum_eDep_NaI = 0.;
    sum_eDep_GAGG = 0.;
    no_Step = 0;
}

//------------------------------------------------------------------------------
  void SensitiveVolume::EndOfEvent(G4HCofThisEvent*)
//------------------------------------------------------------------------------
{
   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   analysisManager->FillH1(0, sum_eDep_Si);
   analysisManager->FillH1(1, sum_eDep_NaI);
   analysisManager->FillH1(2, sum_eDep_GAGG);
   analysisManager->FillH2(0, sum_eDep_Si, sum_eDep_NaI);
   analysisManager->FillH2(1, sum_eDep_Si, sum_eDep_GAGG);
   G4cout << ">>>>>  EnfOfEvent sum_eDep_Si = "<< sum_eDep_Si << G4endl;
   G4cout << ">>>>>  EnfOfEvent sum_eDep_NaI = "<< sum_eDep_NaI << G4endl;
   G4cout << ">>>>>  EnfOfEvent sum_eDep_GAGG = "<< sum_eDep_GAGG << G4endl;
   G4cout << "step:" << doistep++;
}

//------------------------------------------------------------------------------
  G4bool SensitiveVolume::ProcessHits(G4Step* aStep, G4TouchableHistory*)
//------------------------------------------------------------------------------
{
  
//   G4cout << "=== SenstiveVolume-ProcessHits: Output of Information ===" << G4endl;

   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

   G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
   G4TouchableHandle theTouchable = preStepPoint->GetTouchableHandle();
    
// energy deposit in this step and its accumulation over steps
   G4double edep = aStep->GetTotalEnergyDeposit();
   switch(theTouchable->GetCopyNumber()){
   case 3000:
     sum_eDep_NaI = sum_eDep_NaI + edep;
     break;
   case 4000:
     sum_eDep_GAGG = sum_eDep_GAGG + edep;
     break;
   default:
     if(theTouchable->GetCopyNumber(1)==2000){
       sum_eDep_Si = sum_eDep_Si + edep;
     }
     break;
   }
   
   
   if(aStep->GetTrack()->GetTrackStatus()!=fAlive) return false;
   return true;
}






