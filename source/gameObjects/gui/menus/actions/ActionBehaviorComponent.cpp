#include "ActionBehaviorComponent.hpp"

using Barebones::ActionBehaviorComponent;

/******************************************************************************/
ActionBehaviorComponent::ActionBehaviorComponent()
  : Component()
  , mEnabled(true)
{
}

/******************************************************************************/
void ActionBehaviorComponent::Execute()
{
  if(mEnabled)
  {
    ProtectedExecute();
  }
}
