#include "CameraFollowingCharacterState.hpp"

#include "CameraDefaultState.hpp"

using Barebones::CameraFollowingCharacterState;

/******************************************************************************/
CameraFollowingCharacterState::CameraFollowingCharacterState(UrsineEngine::GameObject& aCamera,
                                                             UrsineEngine::GameObject& aCharacter)
  : CameraState(aCamera)
  , mCharacter(&aCharacter)
  , mTargetPosition(0.0, 0.0, 0.0)
  , mYDistance(5.0)
  , mZDistance(5.0)
  , mRotation(-40.0)
  , mSpeed(0.3)
  , mMoving(false)
{
  // Initialize the camera position and orientation.
  aCamera.SetPosition(glm::vec3(0.0,
                                mYDistance,
                                mZDistance));
  //aCamera.SetRotation(mRotation,
  //                    glm::vec3(1.0, 0.0, 0.0));
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingCharacterState::Update()
{
  std::unique_ptr<CameraState> newState = nullptr;

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

        // After the character finishes moving, return to the default
        // camera state.
        newState = std::make_unique<CameraDefaultState>(*camera);
      }
      else
      {
        camera->SetPosition(position);
      }
    }
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingCharacterState::HandleObjectMoved(UrsineEngine::GameObject* aObject)
{
  if(mCharacter == aObject &&
     mCharacter != nullptr)
  {
    // Calculate the new position for the camera.
    auto newPos = mCharacter->GetPosition();
    newPos.y += mYDistance;
    newPos.z += mZDistance;

    mTargetPosition = newPos;
    mMoving = true;
  }

  return nullptr;
}
