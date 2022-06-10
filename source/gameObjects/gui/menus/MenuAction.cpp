#include "MenuAction.hpp"

#include "Signals.hpp"

using Barebones::MenuAction;

/******************************************************************************/
MenuAction::MenuAction(const std::string& aName, const std::string& aDescription)
  : mName(aName)
  , mDescription(aDescription)
  , mEnabled(true)
{
}

/******************************************************************************/
void MenuAction::Execute()
{
  if(mEnabled &&
     mFunction != nullptr)
  {
    mFunction();
  }
}

/******************************************************************************/
void MenuAction::SetEnabled(bool aEnabled)
{
  mEnabled = aEnabled;
  MenuActionEnabledChanged.Notify(*this);
}
