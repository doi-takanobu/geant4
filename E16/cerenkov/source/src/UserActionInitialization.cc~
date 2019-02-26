//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UserActionInitialization.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "UserActionInitialization.hh"
#include "PrimaryGenerator.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

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
  EventAction* eventaction = new EventAction();
  SetUserAction( new PrimaryGenerator() );
  SetUserAction( eventaction );
  SetUserAction( new SteppingAction(eventaction));
  SetUserAction( new RunAction() );
}




