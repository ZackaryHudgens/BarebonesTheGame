#include "CameraState.hpp"

using Barebones::CameraState;

/******************************************************************************/
CameraState::CameraState(UrsineEngine::GameObject& aCamera)
  : mCamera(&aCamera)
{
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::Update()
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter)
{
  return nullptr;
}
