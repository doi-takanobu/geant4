
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ParticleGun.hh"

/// Event action class
///

extern G4double BEAM_ENERGY;
enum{noLG = 1};   // no of detectors
class G4ParticleGun;

class EventAction : public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();

  virtual void    BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);
  inline void AddeDep(G4int i, G4double de) {
    sum_eDep[i] += de;
  }
  inline G4double GetSum(G4int i){
    return sum_eDep[i];
  }
  inline void SetBeamEnergy(G4double E){
    BeamEnergy = E;
  }
  inline G4double GetBeamEnergy(){
    return BeamEnergy;
  }

private:
  G4double  sum_eDep[noLG];
  G4double BeamEnergy;

};

#endif

    
