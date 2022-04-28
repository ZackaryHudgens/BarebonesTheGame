#include "CharacterBehaviorComponent.hpp"

#include <Environment.hpp>

#include "Signals.hpp"

#include "MoveSkill.hpp"

#include "StatusMessageBehaviorComponent.hpp"

using Barebones::CharacterBehaviorComponent;

/******************************************************************************/
CharacterBehaviorComponent::CharacterBehaviorComponent()
  : Component()
  , mTargetPosition(0.0, 0.0, 0.0)
  , mOriginalPosition(0.0, 0.0, 0.0)
  , mSide(Side::eNONE)
  , mSpeed(0.0)
  , mMaximumHealth(1)
  , mCurrentHealth(1)
  , mMoving(false)
  , mRebound(false)
{
}

/******************************************************************************/
void CharacterBehaviorComponent::Initialize()
{
  // All characters have the move skill.
  AddSkill(std::make_unique<MoveSkill>(*GetParent()));

  ProtectedInitialize();
}

/******************************************************************************/
void CharacterBehaviorComponent::Update(double aTime)
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

        // If the rebound flag is set, change the target position to
        // the original position and clear the flag.
        if(mRebound)
        {
          mTargetPosition = mOriginalPosition;
          mRebound = false;
        }
        else
        {
          mMoving = false;
          CharacterFinishedMoving.Notify(*this);
        }
      }
      else
      {
        parent->SetPosition(position);
      }
    }
  }
}

/******************************************************************************/
void CharacterBehaviorComponent::MoveToPosition(const glm::vec3& aPosition,
                                                double aSpeed,
                                                bool aRebound)
{
  mTargetPosition = aPosition;
  mSpeed = aSpeed;
  mRebound = aRebound;

  mMoving = true;

  if(mRebound)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      mOriginalPosition = parent->GetPosition();
    }
  }
}

/******************************************************************************/
std::vector<Barebones::Skill*> CharacterBehaviorComponent::GetSkills()
{
  std::vector<Skill*> skills;

  for(auto& skill : mSkills)
  {
    skills.emplace_back(skill.get());
  }

  return skills;
}

/******************************************************************************/
Barebones::TileList CharacterBehaviorComponent::GetMovements(UrsineEngine::GameObject& aObject,
                                                             const TileLocation& aLocation) const
{
  return TileList();
}

/******************************************************************************/
void CharacterBehaviorComponent::AddSkill(std::unique_ptr<Skill> aSkill)
{
  mSkills.emplace_back(std::move(aSkill));
}

/******************************************************************************/
void CharacterBehaviorComponent::SetMaximumHealth(int aHealth)
{
  mMaximumHealth = aHealth;

  // If the current health is greater than the new maximum health,
  // set the current health to the new maximum.
  if(mCurrentHealth > mMaximumHealth)
  {
    SetCurrentHealth(mMaximumHealth);
  }
}

/******************************************************************************/
void CharacterBehaviorComponent::SetCurrentHealth(int aHealth)
{
  mCurrentHealth = aHealth;

  CharacterHealthChanged.Notify(*this);

  // If the health is below 0, this character is now dead.
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
void CharacterBehaviorComponent::DealDamage(int aValue)
{
  // For now, just do the damage.
  SetCurrentHealth(GetCurrentHealth() - aValue);

  // Create a status message and add it to the scene.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto statusMessageObject = std::make_unique<UrsineEngine::GameObject>("status_message");
    statusMessageObject->AddComponent(std::make_unique<StatusMessageBehaviorComponent>());

    auto parentPos = parent->GetPosition();
    parentPos.z += 0.1;
    statusMessageObject->SetPosition(parentPos);
    statusMessageObject->SetScale(glm::vec3(0.01, 0.01, 1.0));

    auto scene = env.GetCurrentScene();
    if(scene != nullptr)
    {
      scene->AddObject(std::move(statusMessageObject));
    }
  }
}
