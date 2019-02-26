#ifndef _PHYSICSLIST_HH_
#define _PHYSICSLIST_HH_

#include "G4VModularPhysicsList.hh"

class PhysicsList:public G4VModularPhysicsList
{
public:
  PhysicsList();
  ~PhysicsList();

  void SetCuts();
};

#endif
