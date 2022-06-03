#include "ProjectileVisualEffectBehaviorComponent.hpp"

#include <GameObject.hpp>

using Barebones::ProjectileVisualEffectBehaviorComponent;

/******************************************************************************/
ProjectileVisualEffectBehaviorComponent::ProjectileVisualEffectBehaviorComponent(const glm::vec3& aTargetPosition,
                                                                                 double aSpeed)
  : Component()
  , mTargetPosition(aTargetPosition)
  , mSpeed(aSpeed)
{
}

/******************************************************************************/
void ProjectileVisualEffectBehaviorComponent::Update(double aTime)
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
      mSpeed = 0.0;

      parent->ScheduleForDeletion();
    }
    else
    {
      parent->SetPosition(position);
    }
  }
}
