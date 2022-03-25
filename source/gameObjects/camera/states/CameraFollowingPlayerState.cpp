#include "CameraFollowingPlayerState.hpp"

#include "CameraBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

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
  // Initialize the camera position and orientation.
  aCamera.SetPosition(glm::vec3(0.0,
                                mYDistance,
                                mZDistance));
  aCamera.SetRotation(mRotation,
                      glm::vec3(1.0, 0.0, 0.0));
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraFollowingPlayerState::Update()
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
