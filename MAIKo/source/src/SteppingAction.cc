

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "Geometry.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include <cmath>

extern G4int flag;

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVol()
{}


SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  //ある確率で散乱を炭素との強制的に起こす
  
  if(G4UniformRand()<0.1 && flag==0){//10%で散乱を起こす
    flag = 1;
    //get track informations
    G4Track* aTrack = aStep->GetTrack();
    G4ThreeVector pos = aTrack->GetPosition();
    G4ThreeVector dir = aTrack->GetMomentumDirection();
    G4double K = aTrack->GetKineticEnergy();

    //calc. kinematics
    G4double Ex = CLHEP::RandGauss::shoot(2.,0.5);
    G4double cmang = G4UniformRand()*10.*3.14/180.;
    G4double m1 = 9330.64;//MeV 1->3
    G4double m2 = 3728.4;//MeV 2->4
    G4double beta = sqrt((m1+K)*(m1+K)-m1*m1)/(m1+K+m2);
    G4double gamma = 1./sqrt(1-beta*beta);
    G4double E3cm = (((m1+Ex)*(m1+Ex)-m2*m2)/(m1+K+m2)+m1+K+m2)/2.;
    G4double E4cm = (-((m1+Ex)*(m1+Ex)-m2*m2)/(m1+K+m2)+m1+K+m2)/2.;
    G4double pcm = sqrt(E3cm*E3cm-(m1+Ex)*(m1+Ex));
    G4double E3lab = gamma*E3cm+beta*gamma*pcm*cos(cmang);
    G4double E4lab = gamma*E4cm+beta*gamma*(-pcm)*cos(cmang);
    G4double phi = G4UniformRand()*2*3.14;
    G4double p3labx = beta*gamma*E3cm+gamma*pcm*cos(cmang);
    G4double p3laby = pcm*sin(cmang)*cos(phi);
    G4double p3labz = pcm*sin(cmang)*sin(phi);
    G4double p3lab = sqrt(p3labx*p3labx+p3laby*p3laby+p3labz*p3labz);
    G4double p4labx = beta*gamma*E4cm+gamma*(-pcm)*cos(cmang);
    G4double p4laby = -p3laby;
    G4double p4labz = -p3labz;
    G4double p4lab = sqrt(p4labx*p4labx+p4laby*p4laby+p4labz*p4labz);

    //set track informations
    //scattered beam
    G4ThreeVector* p3Vec = new G4ThreeVector(p3labx/p3lab,p3laby/p3lab,p3labz/p3lab);
    aTrack->SetMomentumDirection(*p3Vec);
    aTrack->SetKineticEnergy(E3lab-m1-Ex);

    //recoil particle
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("alpha");
    G4ThreeVector* p4Vec = new G4ThreeVector(p4labx/p4lab,p4laby/p4lab,p4labz/p4lab);
    G4DynamicParticle* dParticle = new G4DynamicParticle(particle,*p4Vec,E4lab-m2);
    G4Track* new_track = new G4Track(dParticle,aTrack->GetGlobalTime(),pos);
    G4TrackVector* sec = fpSteppingManager->GetfSecondary();
    sec->push_back(new_track);
  }
  
//  for(int ii=0;ii<1;ii++){
//    if (!fScoringVol[ii]) {
//        const Geometry* geometry
//             = static_cast<const Geometry*>
//            (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
//	fScoringVol[ii] = geometry->GetScoringVol(ii);
//    }
//  }
//
//  // Get PreStepPoint and TouchableHandle objects
//    G4StepPoint* preStepPoint=step->GetPreStepPoint();
//    G4TouchableHandle theTouchable = preStepPoint->GetTouchableHandle();
//  // 今のステップがある論理物体
//    G4LogicalVolume* volume = theTouchable->GetVolume()->GetLogicalVolume();
//    G4int copyNo = theTouchable->GetCopyNumber();
//
//
////    G4cout << "copy Number = " << copyNo << G4endl;
//    
//  // スコアする論理物体かどうか
//    if (volume != fScoringVol[0]) return;
//  // このステップのエネルギー付与とその積算
//  G4double edepStep = step->GetTotalEnergyDeposit();
//  fEventAction->AddeDep(copyNo-1000, edepStep);      // #0 ~ #19 crystal
}
