#include "CharacterBehaviorComponent.hpp"

#include <algorithm>
#include <sstream>

#include <iostream>

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
  , mType(Type::eNONE)
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
void CharacterBehaviorComponent::AddEffect(std::unique_ptr<Effect> aEffect)
{
  // Display a status message when this effect is added.
  DisplayStatusMessage(aEffect->GetStatusMessage());

  mEffects.emplace_back(std::move(aEffect));
}

/******************************************************************************/
void CharacterBehaviorComponent::RemoveEffect(const std::string& aName)
{
  auto findEffect = [aName](const std::unique_ptr<Effect>& aEffect)
  {
    return aEffect->GetName() == aName;
  };

  auto foundEffect = std::find_if(mEffects.begin(),
                                  mEffects.end(),
                                  findEffect);
  if(foundEffect != mEffects.end())
  {
    // Display a status message when this effect is removed.
    std::stringstream removedMessage;
    removedMessage << foundEffect->get()->GetName() << "\nremoved!";
    DisplayStatusMessage(removedMessage.str());

    mEffects.erase(foundEffect);
  }
}

/******************************************************************************/
std::vector<Barebones::Effect*> CharacterBehaviorComponent::GetEffects()
{
  std::vector<Effect*> effects;

  for(auto& effect : mEffects)
  {
    effects.emplace_back(effect.get());
  }

  return effects;
}

/******************************************************************************/
Barebones::TileList CharacterBehaviorComponent::GetMovements(UrsineEngine::GameObject& aObject,
                                                             const TileLocation& aLocation) const
{
  return TileList();
}

/******************************************************************************/
void CharacterBehaviorComponent::DealDamage(int aValue)
{
  // Apply the damage.
  SetCurrentHealth(GetCurrentHealth() - aValue);

  // Create a status message to display the amount of damage dealt.
  std::stringstream damageText;
  damageText << aValue;
  DisplayStatusMessage(damageText.str());
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
void CharacterBehaviorComponent::DisplayStatusMessage(const std::string& aText)
{
  // Create a status message and add it to the scene.
  auto scene = env.GetCurrentScene();
  auto parent = GetParent();
  if(scene != nullptr &&
     parent != nullptr)
  {
    // Generate a name for the status message object.
    int nameIndex = 0;
    std::stringstream nameStream;
    nameStream << parent->GetName() << "StatusMessage" << aText;

    do
    {
      ++nameIndex;

      nameStream.str("");
      nameStream << parent->GetName() << "StatusMessage" << aText << nameIndex;
    }
    while(scene->GetObject(nameStream.str()) != nullptr);

    // Create the status message object.
    auto statusMessageObject = std::make_unique<UrsineEngine::GameObject>(nameStream.str());
    statusMessageObject->AddComponent(std::make_unique<StatusMessageBehaviorComponent>());
    auto statusMessageComponent = statusMessageObject->GetComponentsOfType<StatusMessageBehaviorComponent>().back();
    statusMessageComponent->SetText(aText);

    // Position the status message to be centered in front of the character.
    auto messagePos = parent->GetPosition();
    messagePos.z += 0.1;
    messagePos.x -= ((statusMessageComponent->GetTextComponent()->GetWidth() * 0.01) / 2.0);
    statusMessageObject->SetPosition(messagePos);
    statusMessageObject->SetScale(glm::vec3(0.01, 0.01, 1.0));

    // Add the status message to the scene.
    scene->AddObject(std::move(statusMessageObject));
  }
}
