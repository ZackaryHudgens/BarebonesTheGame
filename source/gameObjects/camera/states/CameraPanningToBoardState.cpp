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
  // Upon entering this state, place the camera high above and back far enough
  // to view the entire board, then start moving downward towards it.
  SetSpeed(0.1);

  auto camera = GetCamera();
  if(camera != nullptr)
  {
    auto cameraBehaviorComponent = camera->GetFirstComponentOfType<CameraBehaviorComponent>();
    if(cameraBehaviorComponent != nullptr)
    {
      auto board = cameraBehaviorComponent->GetFollowedBoard();
      if(board != nullptr)
      {
        auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
        if(boardLayoutComponent != nullptr)
        {
          int centerColumn = boardLayoutComponent->GetColumns() / 2;
          int centerRow = boardLayoutComponent->GetRows() / 2;

          TileLocation centerLocation(centerColumn, centerRow);
          auto tile = boardLayoutComponent->GetTileAtLocation(centerLocation);
          if(tile != nullptr)
          {
            auto startPos = tile->GetPosition();
            startPos.y += 25.0;
            startPos.z += 9.0;

            camera->SetPosition(startPos);

            auto targetPos = startPos;
            targetPos.y -= 17.0;
            SetTargetPosition(targetPos);
          }
        }
      }
    }
  }
}

/******************************************************************************/
void CameraPanningToBoardState::OnExit()
{
  auto camera = GetCamera();
  if(camera != nullptr)
  {
    CameraFinishedInitialSequence.Notify(*camera);
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
