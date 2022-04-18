#include "CameraFollowingPlayerState.hpp"

#include "CameraBehaviorComponent.hpp"
#include "CameraDefaultState.hpp"

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerBehaviorComponent.hpp"

#include <iostream>

using Barebones::CameraFollowingPlayerState;

/******************************************************************************/
CameraFollowingPlayerState::CameraFollowingPlayerState(UrsineEngine::GameObject& aCamera,
                                                       UrsineEngine::GameObject& aPlayer)
  : CameraState(aCamera)
  , mPlayer(&aPlayer)
  , mTargetPosition(0.0, 0.0, 0.0)
  , mYDistance(5.0)
  , mZDistance(5.0)
  , mRotation(-40.0)
  , mSpeed(0.3)
  , mMoving(false)
{
  // Upon entering this state, calculate the target position
  // using the player's position.
  auto cameraBehaviorComponent = aCamera.GetFirstComponentOfType<CameraBehaviorComponent>();
  if(cameraBehaviorComponent != nullptr)
  {
    auto board = cameraBehaviorComponent->GetFollowedBoard();
    if(board != nullptr)
    {
      auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
      auto humanPlayerBehaviorComponent = aPlayer.GetFirstComponentOfType<HumanPlayerBehaviorComponent>();
      if(boardLayoutComponent != nullptr &&
         humanPlayerBehaviorComponent != nullptr)
      {
        auto tile = boardLayoutComponent->GetTileAtLocation(humanPlayerBehaviorComponent->GetLocation());
        if(tile != nullptr)
        {
          mTargetPosition = tile->GetPosition();
          mTargetPosition.y += mYDistance;
          mTargetPosition.z += mZDistance;

          mMoving = true;
        }
      }
    }
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingPlayerState::Update(double aTime)
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
std::unique_ptr<Barebones::CameraState> CameraFollowingPlayerState::HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer)
{
  std::unique_ptr<CameraState> newState;

  if(aPlayer.GetParent() == mPlayer)
  {
    // Get the board that this camera is following, then get the tile
    // at the player's new location and use it to calculate the new
    // target position for the camera.
    auto cameraObject = GetCamera();
    if(cameraObject != nullptr)
    {
      auto cameraBehaviorComponent = cameraObject->GetFirstComponentOfType<CameraBehaviorComponent>();
      if(cameraBehaviorComponent != nullptr)
      {
        auto boardObject = cameraBehaviorComponent->GetFollowedBoard();
        if(boardObject != nullptr)
        {
          auto boardLayoutComponent = boardObject->GetFirstComponentOfType<BoardLayoutComponent>();
          if(boardLayoutComponent != nullptr)
          {
            auto tile = boardLayoutComponent->GetTileAtLocation(aPlayer.GetLocation());
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
        }
      }
    }
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingPlayerState::HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer)
{
  std::unique_ptr<CameraState> newState = nullptr;

  // If the player whose turn ended was the player being followed,
  // revert to the default state.
  if(aPlayer.GetParent() == mPlayer)
  {
    auto camera = GetCamera();
    if(camera != nullptr)
    {
      newState = std::make_unique<CameraDefaultState>(*camera);
    }
  }

  return newState;
}
