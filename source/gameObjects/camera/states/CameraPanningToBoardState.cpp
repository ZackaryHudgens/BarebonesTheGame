#include "CameraPanningToBoardState.hpp"

#include "BoardLayoutComponent.hpp"
#include "CameraBehaviorComponent.hpp"

#include "CameraDefaultState.hpp"

using Barebones::CameraPanningToBoardState;

/******************************************************************************/
CameraPanningToBoardState::CameraPanningToBoardState(UrsineEngine::GameObject& aCamera)
  : CameraMovingState(aCamera)
{
}

/******************************************************************************/
void CameraPanningToBoardState::OnEnter()
{
  SetSpeed(0.01);

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
          // Get the tile in the center of the board and set the target position
          // using that tile.
          int centerColumn = boardLayoutComponent->GetColumns() / 2;
          int centerRow = boardLayoutComponent->GetRows() / 2;

          TileLocation centerLocation(centerColumn, centerRow);
          auto tile = boardLayoutComponent->GetTileAtLocation(centerLocation);
          if(tile != nullptr)
          {
            auto tilePos = tile->GetPosition();
            tilePos.y += 7.0;
            tilePos.z += 7.0;

            SetTargetPosition(tilePos);
          }
        }
      }
    }
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
