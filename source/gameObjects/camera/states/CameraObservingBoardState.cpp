#include "CameraObservingBoardState.hpp"

#include "BoardLayoutComponent.hpp"

#include "CameraFollowingCharacterState.hpp"
#include "CameraFollowingPlayerState.hpp"

using Barebones::CameraObservingBoardState;

/******************************************************************************/
CameraObservingBoardState::CameraObservingBoardState(UrsineEngine::GameObject& aCamera,
                                                     UrsineEngine::GameObject& aBoard)
  : CameraState(aCamera)
  , mTargetPosition(0.0, 0.0, 0.0)
  , mYDistance(7.0)
  , mZDistance(7.0)
  , mRotation(-40.0)
  , mSpeed(0.3)
{
  // Upon entering this state, calculate the target position
  // of the camera using the tile in the center of the board.
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    TileLocation centerTile;
    centerTile.first = boardLayoutComponent->GetColumns() / 2;
    centerTile.second = boardLayoutComponent->GetRows() / 2;

    auto tile = boardLayoutComponent->GetTileAtLocation(centerTile);
    if(tile != nullptr)
    {
      // Calculate the new position for the camera.
      auto newPos = tile->GetPosition();
      newPos.y += mYDistance;
      newPos.z += mZDistance;

      mTargetPosition = newPos;
      mMoving = true;
    }
  }

  aCamera.SetRotation(mRotation,
                      glm::vec3(1.0, 0.0, 0.0));
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraObservingBoardState::Update()
{
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
std::unique_ptr<Barebones::CameraState> CameraObservingBoardState::HandleBoardFollowed(UrsineEngine::GameObject& aBoard)
{
  // Update the target position of the camera for the new board.
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    TileLocation centerTile;
    centerTile.first = boardLayoutComponent->GetColumns() / 2;
    centerTile.second = boardLayoutComponent->GetRows() / 2;

    auto tile = boardLayoutComponent->GetTileAtLocation(centerTile);
    if(tile != nullptr)
    {
      // Calculate the new position for the camera.
      auto newPos = tile->GetPosition();
      newPos.y += mYDistance;
      newPos.z += mZDistance;

      mTargetPosition = newPos;
      mMoving = true;
    }
  }

  return nullptr;
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraObservingBoardState::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  std::unique_ptr<CameraState> newState = nullptr;

  // If the player is human, swap to the Following Player state.
  if(dynamic_cast<HumanPlayerBehaviorComponent*>(&aPlayer) != nullptr)
  {
    auto camera = GetCamera();
    auto playerParent = aPlayer.GetParent();
    if(camera != nullptr &&
       playerParent != nullptr)
    {
      newState = std::make_unique<CameraFollowingPlayerState>(*camera,
                                                              *playerParent);
    }
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraObservingBoardState::HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter)
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

  return newState;
}
