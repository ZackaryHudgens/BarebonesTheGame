#include "CameraFollowingCharacterState.hpp"

using Barebones::CameraFollowingCharacterState;

/******************************************************************************/
CameraFollowingCharacterState::CameraFollowingCharacterState(UrsineEngine::GameObject& aCamera,
                                                             UrsineEngine::GameObject& aCharacter)
  : CameraState(aCamera)
  , mCharacter(&aCharacter)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingCharacterState::Update()
{
  std::unique_ptr<CameraState> newState = nullptr;
  return newState;
}

/******************************************************************************/
void CameraFollowingCharacterState::HandleObjectMoved(UrsineEngine::GameObject* aObject)
{
}
