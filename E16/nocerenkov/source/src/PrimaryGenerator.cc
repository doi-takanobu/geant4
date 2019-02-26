//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PrimaryGenerator.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "PrimaryGenerator.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "EventAction.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"
#include "G4Event.hh"

extern G4double BEAM_ENERGY;
G4int Run_No=0;
//------------------------------------------------------------------------------
  PrimaryGenerator::PrimaryGenerator()
    : fpParticleGun(0) 
//------------------------------------------------------------------------------
{
}

//------------------------------------------------------------------------------
  PrimaryGenerator::~PrimaryGenerator()
//------------------------------------------------------------------------------
{
  delete fpParticleGun;
}

//------------------------------------------------------------------------------
  void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
//------------------------------------------------------------------------------
{
  G4double pos_X = 0.*cm;
  G4double pos_Y = 0.*cm;
  G4double pos_Z = 200.*cm;
  G4ThreeVector position = G4ThreeVector(pos_X,pos_Y,pos_Z);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
 
  G4String particlename = "e-"; 
  G4ParticleDefinition* particle = particleTable->FindParticle(particlename);
  G4double energy = 200*(++Run_No)*MeV;
  BEAM_ENERGY = energy;
  G4double beam_X = 0.;
  G4double beam_Y = 0.;
  G4double beam_Z =  -1.;
  G4ThreeVector momentumDirection = G4ThreeVector(beam_X,beam_Y,beam_Z);
  fpParticleGun = new G4ParticleGun();
  {
    fpParticleGun->SetParticleDefinition(particle);
    fpParticleGun->SetParticleEnergy(energy);
    fpParticleGun->SetParticleMomentumDirection(momentumDirection);
  }
  
  fpParticleGun->SetParticlePosition(position);

  fpParticleGun->GeneratePrimaryVertex(anEvent);

}

