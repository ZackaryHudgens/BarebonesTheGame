#include "SkillMenuLayoutComponent.hpp"

#include <GameObject.hpp>
#include <MeshComponent.hpp>

#include <iostream>

using Barebones::SkillMenuLayoutComponent;

/******************************************************************************/
SkillMenuLayoutComponent::SkillMenuLayoutComponent()
  : MenuLayoutComponent()
  , mIconSpacing(100.0)
  , mTargetPosition(0.0, 0.0, 0.0)
  , mSpeed(0.3)
  , mMoving(false)
{
}

/******************************************************************************/
void SkillMenuLayoutComponent::Initialize()
{
  mTargetPosition = glm::vec3(0.0,
                              300.0,
                              0.0);
  mMoving = true;
}

/******************************************************************************/
void SkillMenuLayoutComponent::Update()
{
  if(mMoving)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto position = glm::mix(parent->GetPosition(),
                               mTargetPosition,
                               mSpeed);

      // If the position is close enough to the target position,
      // move directly to the target position and stop moving.
      if(std::abs(mTargetPosition.x - position.x) <= 0.005 &&
         std::abs(mTargetPosition.y - position.y) <= 0.005 &&
         std::abs(mTargetPosition.z - position.z) <= 0.005)
      {
        parent->SetPosition(mTargetPosition);
        mMoving = false;
      }
      else
      {
        parent->SetPosition(position);
      }
    }
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionAdded()
{
  int xDistance = 200;
  int index = 1;
  for(auto& action : GetActions())
  {
    action->SetPosition(glm::vec3(xDistance * index,
                                  0.0,
                                  0.0));
    ++index;
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionSelected()
{
  // When a skill is selected, this menu is no longer needed.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->ScheduleForDeletion();
  }
}
