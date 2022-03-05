#include "CharacterBehaviorComponent.hpp"

#include "MoveSkillComponent.hpp"

using Barebones::CharacterBehaviorComponent;

/******************************************************************************/
CharacterBehaviorComponent::CharacterBehaviorComponent()
  : Component()
  , mTargetPosition(0.0, 0.0, 0.0)
  , mSpeed(0.0)
  , mMaximumHealth(1)
  , mCurrentHealth(1)
  , mMoving(false)
{
}

/******************************************************************************/
void CharacterBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // All characters have the Move skill by default.
    parent->AddComponent(std::make_unique<MoveSkillComponent>());

    // Add the rest of the skills.
    AddSkills();
  }
}

/******************************************************************************/
void CharacterBehaviorComponent::Update()
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

  ProtectedUpdate();
}

/******************************************************************************/
void CharacterBehaviorComponent::MoveToPosition(const glm::vec3& aPosition,
                                                double aSpeed)
{
  mTargetPosition = aPosition;
  mSpeed = aSpeed;
  mMoving = true;
}

/******************************************************************************/
Barebones::TileList CharacterBehaviorComponent::GetMovements(UrsineEngine::GameObject& aObject,
                                                             const TileLocation& aLocation) const
{
  return TileList();
}

/******************************************************************************/
void CharacterBehaviorComponent::DealDamage(int aDamage)
{
  int newHealth = GetCurrentHealth() - aDamage;
  SetCurrentHealth(newHealth);
}

/******************************************************************************/
void CharacterBehaviorComponent::SetMaximumHealth(int aHealth)
{
  mMaximumHealth = aHealth;

  if(mCurrentHealth > mMaximumHealth)
  {
    SetCurrentHealth(mMaximumHealth);
  }
}

/******************************************************************************/
void CharacterBehaviorComponent::SetCurrentHealth(int aHealth)
{
  mCurrentHealth = aHealth;

  if(mCurrentHealth <= 0)
  {
    CharacterDied.Notify(*this);

    auto parent = GetParent();
    if(parent != nullptr)
    {
      parent->ScheduleForDeletion();
    }
  }
}

/******************************************************************************/
Barebones::CharacterDiedSignal Barebones::CharacterDied;
