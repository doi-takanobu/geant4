

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "Geometry.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVol()
{}


SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
  for(int ii=0;ii<1;ii++){
    if (!fScoringVol[ii]) {
        const Geometry* geometry
             = static_cast<const Geometry*>
            (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	fScoringVol[ii] = geometry->GetScoringVol(ii);
    }
  }

  // Get PreStepPoint and TouchableHandle objects
    G4StepPoint* preStepPoint=step->GetPreStepPoint();
    G4TouchableHandle theTouchable = preStepPoint->GetTouchableHandle();
  // 今のステップがある論理物体
    G4LogicalVolume* volume = theTouchable->GetVolume()->GetLogicalVolume();
    G4int copyNo = theTouchable->GetCopyNumber();


//    G4cout << "copy Number = " << copyNo << G4endl;
    
  // スコアする論理物体かどうか
    if (volume != fScoringVol[0]) return;
  // このステップのエネルギー付与とその積算
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddeDep(copyNo-1000, edepStep);      // #0 ~ #19 crystal
}



