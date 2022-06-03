#include "CameraFollowingCharacterState.hpp"

#include "CameraBehaviorComponent.hpp"
#include "CameraDefaultState.hpp"

#include "Signals.hpp"

using Barebones::CameraFollowingCharacterState;

/******************************************************************************/
CameraFollowingCharacterState::CameraFollowingCharacterState(UrsineEngine::GameObject& aCamera,
                                                             UrsineEngine::GameObject& aCharacter)
  : CameraState(aCamera)
  , mCharacter(&aCharacter)
  , mYDistance(5.0)
  , mZDistance(5.0)
  , mRotation(-40.0)
  , mSpeed(0.3)
  , mMoving(true)
{
  mTargetPosition = aCharacter.GetPosition();
  mTargetPosition.y += mYDistance;
  mTargetPosition.z += mZDistance;
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingCharacterState::Update(double aTime)
{
  if(mMoving)
  {
    auto camera = GetCamera();
    if(camera != nullptr)
    {
      auto position = glm::mix(camera->GetPosition(),
                               mTargetPosition,
                               mSpeed);

      // If the position is close enough to the target position,
      // move directly to the target position and stop moving.
      if(std::abs(mTargetPosition.x - position.x) <= 0.005 &&
         std::abs(mTargetPosition.y - position.y) <= 0.005 &&
         std::abs(mTargetPosition.z - position.z) <= 0.005)
      {
        camera->SetPosition(mTargetPosition);
        mMoving = false;

        CameraFinishedMoving.Notify();
      }
      else
      {
        camera->SetPosition(position);
      }
    }
  }

  return nullptr;
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingCharacterState::HandleObjectMoved(UrsineEngine::GameObject* aObject)
{
  if(mCharacter == aObject)
  {
    mTargetPosition = aObject->GetPosition();
    mTargetPosition.y += mYDistance;
    mTargetPosition.z += mZDistance;

    mMoving = true;
  }

  return nullptr;
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingCharacterState::HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter)
{
  std::unique_ptr<CameraState> newState = nullptr;

  // If the character that ended its turn is the same as the character
  // being followed, revert to the default state.
  if(aCharacter.GetParent() == mCharacter)
  {
    auto camera = GetCamera();
    if(camera != nullptr)
    {
      newState = std::make_unique<CameraDefaultState>(*camera);
    }
  }

  return newState;
}
