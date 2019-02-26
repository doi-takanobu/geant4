
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

enum{noSi = 1,noNaI = 1,noGAGG = 1};   // no of detectors

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

private:
  G4double  sum_eDep[noSi+noNaI+noGAGG];

};

#endif

    
