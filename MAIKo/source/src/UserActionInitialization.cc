//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UserActionInitialization.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "UserActionInitialization.hh"
#include "PrimaryGenerator.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

G4int flag = 0;

//------------------------------------------------------------------------------
  UserActionInitialization::UserActionInitialization()
  : G4VUserActionInitialization()
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  UserActionInitialization::~UserActionInitialization()
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
void UserActionInitialization::Build() const
//------------------------------------------------------------------------------
{
  flag = 0;
  EventAction* eventaction = new EventAction();
  SetUserAction( new PrimaryGenerator() );
  SetUserAction( eventaction );
  SetUserAction( new SteppingAction(eventaction));
  SetUserAction( new RunAction() );
}




