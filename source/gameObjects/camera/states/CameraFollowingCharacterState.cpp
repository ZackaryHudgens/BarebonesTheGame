#include "CameraFollowingCharacterState.hpp"

#include "CameraBehaviorComponent.hpp"
#include "CameraDefaultState.hpp"

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
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingCharacterState::Update(double aTime)
{
  if(mMoving)
  {
    auto camera = GetCamera();
    if(camera != nullptr &&
       mCharacter != nullptr)
    {
      auto targetPosition = mCharacter->GetPosition();
      targetPosition.y += mYDistance;
      targetPosition.z += mZDistance;

      auto cameraBehaviorComponent = camera->GetFirstComponentOfType<CameraBehaviorComponent>();
      if(cameraBehaviorComponent != nullptr)
      {
        auto zoomDistance = cameraBehaviorComponent->GetZoomDistance();
        targetPosition.y += zoomDistance;
        targetPosition.z += zoomDistance;
      }

      auto position = glm::mix(camera->GetPosition(),
                               targetPosition,
                               mSpeed);

      // If the position is close enough to the target position,
      // move directly to the target position and stop moving.
      if(std::abs(targetPosition.x - position.x) <= 0.005 &&
         std::abs(targetPosition.y - position.y) <= 0.005 &&
         std::abs(targetPosition.z - position.z) <= 0.005)
      {
        camera->SetPosition(targetPosition);
        mMoving = false;
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
