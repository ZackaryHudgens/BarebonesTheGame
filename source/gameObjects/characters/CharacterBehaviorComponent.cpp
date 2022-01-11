#include "CharacterBehaviorComponent.hpp"

using Barebones::CharacterBehaviorComponent;

/******************************************************************************/
CharacterBehaviorComponent::CharacterBehaviorComponent()
  : Component()
  , mHorizontalDistance(0)
  , mVerticalDistance(0)
  , mDiagonalDistance(0)
{
}
