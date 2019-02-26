//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PrimaryGenerator.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "PrimaryGenerator.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"

//------------------------------------------------------------------------------
  PrimaryGenerator::PrimaryGenerator()
    : fpParticleGun1(0),fpParticleGun2(0) 
//------------------------------------------------------------------------------
{
}

//------------------------------------------------------------------------------
  PrimaryGenerator::~PrimaryGenerator()
//------------------------------------------------------------------------------
{
  delete fpParticleGun1;
  delete fpParticleGun2;
}

//------------------------------------------------------------------------------
  void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
//------------------------------------------------------------------------------
{
  G4double MaxEnergy = 100.;
  G4double pos_X = 0.*cm;
  G4double pos_Y = 0.*cm;
  G4double pos_Z = 40.*cm;
  G4ThreeVector position = G4ThreeVector(pos_X,pos_Y,pos_Z);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
 
  G4String particlename = "e-"; 
  switch((G4int)(G4UniformRand()*5)%5){
  case 0:
    particlename = "proton";
    MaxEnergy = 100.;
    break;
  case 1:
    particlename = "deuteron";
    MaxEnergy = 100.;
    break;
  case 2:
    particlename = "triton";
    MaxEnergy = 100.;
    break;
  case 3:
    particlename = "He3";
    MaxEnergy = 100.;
    break;
  case 4:
    particlename = "alpha";
    MaxEnergy = 100.;
    break;
  default:
    break;
  }
  G4ParticleDefinition* particle = particleTable->FindParticle(particlename);
  G4double energy = MaxEnergy*pow(G4UniformRand(),1)*MeV;
  G4double beam_X = (G4UniformRand()-0.5);
  G4double beam_Y = (G4UniformRand()-0.5);
  G4double beam_Z =  -8.;
  G4ThreeVector momentumDirection = G4ThreeVector(beam_X,beam_Y,beam_Z);
  fpParticleGun1 = new G4ParticleGun();
  {
    fpParticleGun1->SetParticleDefinition(particle);
    fpParticleGun1->SetParticleEnergy(energy);
    fpParticleGun1->SetParticleMomentumDirection(momentumDirection);
  }

  //fpParticleGun2 = new G4ParticleGun();
  //{
    //fpParticleGun2->SetParticleDefinition(particle);
    //fpParticleGun2->SetParticleEnergy(energy);
    //fpParticleGun2->SetParticleMomentumDirection(momentumDirection);
    //}
  
  fpParticleGun1->SetParticlePosition(position);

  //pos_Y = -0.5*cm;
  //position = G4ThreeVector(pos_X,pos_Y,pos_Z);

  //fpParticleGun2->SetParticlePosition(position);

  //G4int LoopMax = 1;
 

  //for(G4int ii=0;ii<LoopMax;ii++){
    fpParticleGun1->GeneratePrimaryVertex(anEvent);
    //fpParticleGun2->GeneratePrimaryVertex(anEvent);
    //}
}

