#include "CharacterMovingState.hpp"

#include <GameObject.hpp>

#include "CharacterDefaultState.hpp"
#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::CharacterMovingState;

/******************************************************************************/
CharacterMovingState::CharacterMovingState(UrsineEngine::GameObject& aCharacter,
                                           const glm::vec3& aPosition,
                                           double aSpeed)
  : CharacterState(aCharacter)
  , mTargetPosition(aPosition)
  , mSpeed(aSpeed)
{
}

/******************************************************************************/
void CharacterMovingState::OnExit()
{
  auto character = GetCharacter();
  if(character != nullptr)
  {
    auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(characterBehaviorComponent != nullptr)
    {
      CharacterFinishedMoving.Notify(*characterBehaviorComponent);
    }
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::CharacterState> CharacterMovingState::Update(double aTime)
{
  std::unique_ptr<CharacterState> newState = nullptr;

  auto character = GetCharacter();
  if(character != nullptr)
  {
    auto position = glm::mix(character->GetPosition(),
                             mTargetPosition,
                             mSpeed);

    // If the position is close enough to the target position,
    // move directly to the target position and stop moving.
    if(std::abs(mTargetPosition.x - position.x) <= 0.005 &&
       std::abs(mTargetPosition.y - position.y) <= 0.005 &&
       std::abs(mTargetPosition.z - position.z) <= 0.005)
    {
      character->SetPosition(mTargetPosition);
      mSpeed = 0.0;

      // Revert to the default state.
      newState = std::make_unique<CharacterDefaultState>(*character);
    }
    else
    {
      character->SetPosition(position);
    }
  }

  return newState;
}
