#include "BasicHumanBehaviorComponent.hpp"

using Barebones::BasicHumanBehaviorComponent;

/******************************************************************************/
BasicHumanBehaviorComponent::BasicHumanBehaviorComponent()
  : CharacterBehaviorComponent()
{
  SetMaximumHealth(5);
  SetCurrentHealth(5);
}
