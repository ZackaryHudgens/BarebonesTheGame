#include "CameraPanningToBoardState.hpp"

#include "BoardLayoutComponent.hpp"
#include "CameraBehaviorComponent.hpp"

#include "CameraDefaultState.hpp"

#include "Signals.hpp"

using Barebones::CameraPanningToBoardState;

/******************************************************************************/
CameraPanningToBoardState::CameraPanningToBoardState(UrsineEngine::GameObject& aCamera)
  : CameraMovingState(aCamera)
{
}

/******************************************************************************/
void CameraPanningToBoardState::OnEnter()
{
  SetSpeed(0.1);

  auto camera = GetCamera();
  if(camera != nullptr)
  {
    auto targetPos = camera->GetPosition();
    targetPos.y -= 8.0;

    SetTargetPosition(targetPos);
  }
}

/******************************************************************************/
void CameraPanningToBoardState::OnExit()
{
  auto camera = GetCamera();
  if(camera != nullptr)
  {
    CameraFinishedMovingToBoard.Notify(*camera);
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraPanningToBoardState::HandleTargetPositionReached()
{
  std::unique_ptr<CameraState> newState = nullptr;

  auto camera = GetCamera();
  if(camera != nullptr)
  {
    newState = std::make_unique<CameraDefaultState>(*camera);
  }

  return std::move(newState);
}
