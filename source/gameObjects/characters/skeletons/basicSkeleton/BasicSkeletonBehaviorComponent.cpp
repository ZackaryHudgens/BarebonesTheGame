#include "BasicSkeletonBehaviorComponent.hpp"

#include "ClawSkill.hpp"

using Barebones::BasicSkeletonBehaviorComponent;

/******************************************************************************/
BasicSkeletonBehaviorComponent::BasicSkeletonBehaviorComponent()
  : CharacterBehaviorComponent()
  , mHorizontalMovement(2)
  , mVerticalMovement(2)
{
  SetName("Basic Skeleton");
  SetType(Type::eSKELETON);
  SetMaximumHealth(10);
  SetCurrentHealth(10);
  SetSpeed(7);
}

/******************************************************************************/
void BasicSkeletonBehaviorComponent::ProtectedInitialize()
{
  AddSkill(std::make_unique<ClawSkill>(*GetParent()));
}
