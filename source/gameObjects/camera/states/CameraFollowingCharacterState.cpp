#include "CameraFollowingCharacterState.hpp"

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
{
  // Initialize the camera position and orientation.
  aCamera.SetPosition(glm::vec3(aCharacter.GetPosition().x,
                                mYDistance,
                                mZDistance));
  //aCamera.SetRotation(mRotation,
  //                    glm::vec3(1.0, 0.0, 0.0));
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

    auto camera = GetCamera();
    if(camera != nullptr)
    {
      camera->SetPosition(newPos);
    }
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
