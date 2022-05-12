#include "BasicSkeletonBehaviorComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "BoardLayoutComponent.hpp"

#include "ClawSkill.hpp"

using Barebones::BasicSkeletonBehaviorComponent;

/******************************************************************************/
BasicSkeletonBehaviorComponent::BasicSkeletonBehaviorComponent()
  : CharacterBehaviorComponent()
{
  SetName("Basic Skeleton");
  SetType(Type::eSKELETON);
  SetMaximumHealth(10);
  SetCurrentHealth(10);
  SetSpeed(4);
}

/******************************************************************************/
void BasicSkeletonBehaviorComponent::ProtectedInitialize()
{
  AddSkill(std::make_unique<ClawSkill>(*GetParent()));
}
