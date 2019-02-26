#ifndef _USEREVENTINFORMATION_HH_
#define _USEREVENTINFORMATION_HH_

#include "G4VUserEventInformation.hh"
#include "globals.hh"

class UserEventInformation : public G4VUserEventInformation
{
public:
  UserEventInformation();
  virtual ~UserEventInformation();
  void Print();
  void SetBeamEnergy(G4double E);
  G4double GetBeamEnergy();
protected:
  G4double BeamEnergy;
};

#endif
