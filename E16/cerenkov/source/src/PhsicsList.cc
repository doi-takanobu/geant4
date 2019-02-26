#include "PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4OpticalProcessIndex.hh"

PhysicsList::PhysicsList():G4VModularPhysicsList()
{
  RegisterPhysics(new G4DecayPhysics());//Default physics
  RegisterPhysics(new G4RadioactiveDecayPhysics());//Radioactive decay
  RegisterPhysics(new G4EmStandardPhysics());//EM physics

  //Optical Photon physics
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  RegisterPhysics(opticalPhysics);

  opticalPhysics->SetScintillationYieldFactor(1.0);
  opticalPhysics->SetScintillationExcitationRatio(0.0);
  opticalPhysics->SetMaxNumPhotonsPerStep(100);
  opticalPhysics->SetMaxBetaChangePerStep(10.0);
  opticalPhysics->SetTrackSecondariesFirst(kCerenkov,true);
  opticalPhysics->SetTrackSecondariesFirst(kScintillation,true);
}

PhysicsList::~PhysicsList()
{
}

void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}
  
