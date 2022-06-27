#include "CameraState.hpp"

using Barebones::CameraState;

/******************************************************************************/
CameraState::CameraState(UrsineEngine::GameObject& aCamera)
  : mCamera(&aCamera)
{
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::Update(double aTime)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::HandleObjectMoved(UrsineEngine::GameObject* aObject)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<CameraState> CameraState::HandleCameraZoomChanged(double aZoom)
{
  return nullptr;
}
