#include "CameraFollowingPlayerState.hpp"

#include "BoardLayoutComponent.hpp"
#include "CameraBehaviorComponent.hpp"

#include "CameraDefaultState.hpp"
#include "CameraFollowingCharacterState.hpp"

#include "Signals.hpp"

using Barebones::CameraFollowingPlayerState;

/******************************************************************************/
CameraFollowingPlayerState::CameraFollowingPlayerState(UrsineEngine::GameObject& aCamera,
                                                       PlayerBehaviorComponent& aPlayer)
  : CameraMovingState(aCamera)
  , mPlayer(&aPlayer)
{
  BoardFocusedTileChanged.Connect(mObserver, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleBoardFocusedTileChanged(aBoard);
  });
}

/******************************************************************************/
void CameraFollowingPlayerState::OnEnter()
{
  // Set the movement speed, then set the target position.
  SetSpeed(0.3);

  auto camera = GetCamera();
  if(camera != nullptr)
  {
    auto cameraBehaviorComponent = camera->GetFirstComponentOfType<CameraBehaviorComponent>();
    if(cameraBehaviorComponent != nullptr)
    {
      auto board = cameraBehaviorComponent->GetFollowedBoard();
      if(board != nullptr)
      {
        HandleBoardFocusedTileChanged(*board);
      }
    }
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingPlayerState::HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer)
{
  std::unique_ptr<CameraState> newState = nullptr;

  // If the player whose turn ended is the player being followed, revert
  // to the default state.
  if(&aPlayer == mPlayer)
  {
    auto camera = GetCamera();
    if(camera != nullptr)
    {
      newState = std::make_unique<CameraDefaultState>(*camera);
    }
  }

  return std::move(newState);
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingPlayerState::HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter)
{
  std::unique_ptr<CameraState> newState = nullptr;

  // Swap to the Following Character state, if possible.
  auto camera = GetCamera();
  auto characterParent = aCharacter.GetParent();
  if(camera != nullptr &&
     characterParent != nullptr)
  {
    newState = std::make_unique<CameraFollowingCharacterState>(*camera,
                                                               *characterParent);
  }

  return std::move(newState);
}

/******************************************************************************/
void CameraFollowingPlayerState::HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard)
{
  // If the given board is the board the camera is following, update the
  // target position to view the currently focused tile.
  auto camera = GetCamera();
  if(camera != nullptr)
  {
    auto cameraBehaviorComponent = camera->GetFirstComponentOfType<CameraBehaviorComponent>();
    if(cameraBehaviorComponent != nullptr)
    {
      auto board = cameraBehaviorComponent->GetFollowedBoard();
      if(&aBoard == board)
      {
        auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
        if(boardLayoutComponent != nullptr)
        {
          auto focusedLocation = boardLayoutComponent->GetFocusedTileLocation();
          auto focusedTile = boardLayoutComponent->GetTileAtLocation(focusedLocation);

          if(focusedTile != nullptr)
          {
            auto pos = focusedTile->GetPosition();
            pos.y += 5.0;
            pos.z += 5.0;

            SetTargetPosition(pos);
          }
        }
      }
    }
  }
}
