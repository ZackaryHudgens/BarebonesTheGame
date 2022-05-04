#include "CharacterShakingState.hpp"

#include "CharacterDefaultState.hpp"

using Barebones::CharacterShakingState;

/******************************************************************************/
CharacterShakingState::CharacterShakingState(UrsineEngine::GameObject& aCharacter)
  : CharacterState(aCharacter)
  , mSpeed(0.9)
  , mOffset(0.15)
{
  mOriginalPosition = aCharacter.GetPosition();

  mTargetPosition = mOriginalPosition;
  mTargetPosition.x += mOffset;
}

/******************************************************************************/
std::unique_ptr<Barebones::CharacterState> CharacterShakingState::Update(double aTime)
{
  std::unique_ptr<CharacterState> newState = nullptr;

  auto character = GetCharacter();
  if(character != nullptr)
  {
    auto position = glm::mix(character->GetPosition(),
                             mTargetPosition,
                             mSpeed);

    // If the position is close enough to the target position,
    // move directly to the target position.
    if(std::abs(mTargetPosition.x - position.x) <= 0.005 &&
       std::abs(mTargetPosition.y - position.y) <= 0.005 &&
       std::abs(mTargetPosition.z - position.z) <= 0.005)
    {
      // Set the new target position using the offset value.
      // If the offset value has been exhausted, return to the
      // original position and stop shaking.
      mOffset -= 0.01;
      if(mOffset <= 0.0)
      {
        // Move to the original position.
        character->SetPosition(mOriginalPosition);

        // Return to the default state.
        newState = std::make_unique<CharacterDefaultState>(*character);
      }
      else if(mTargetPosition.x >= mOriginalPosition.x)
      {
        character->SetPosition(mTargetPosition);
      
        // We were moving to the right before; now move to the left.
        mTargetPosition = mOriginalPosition;
        mTargetPosition.x -= mOffset;
      }
      else
      {
        character->SetPosition(mTargetPosition);

        // We were moving to the left before; now move to the right.
        mTargetPosition = mOriginalPosition;
        mTargetPosition.x += mOffset;
      }
    }
    else
    {
      character->SetPosition(position);
    }
  }

  return newState;
}
