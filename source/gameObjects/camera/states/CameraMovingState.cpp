#include "CameraMovingState.hpp"

#include "CameraBehaviorComponent.hpp"

using Barebones::CameraMovingState;

/******************************************************************************/
CameraMovingState::CameraMovingState(UrsineEngine::GameObject& aCamera)
  : CameraState(aCamera)
  , mTargetPosition(0.0, 0.0, 0.0)
  , mSpeed(0.0)
  , mMoving(false)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::CameraState> CameraMovingState::Update(double aTime)
{
  std::unique_ptr<CameraState> newState = nullptr;

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

        newState = HandleTargetPositionReached();
      }
      else
      {
        camera->SetPosition(position);
      }
    }
  }

  return std::move(newState);
}

/******************************************************************************/
void CameraMovingState::HandleCameraZoomChange(bool aZoom)
{
  auto camera = GetCamera();
  if(camera != nullptr)
  {
    // If the camera was moving when the zoom change happened, apply the zoom
    // to the current target position. Otherwise, apply it to the camera's
    // current position.
    auto targetPos = camera->GetPosition();
    if(mMoving)
    {
      targetPos = mTargetPosition;
    }

    if(aZoom)
    {
      targetPos.y += 2.5;
      targetPos.z += 2.5;
    }
    else
    {
      targetPos.y -= 2.5;
      targetPos.z -= 2.5;
    }

    mTargetPosition = targetPos;
    mMoving = true;
  }
}

/******************************************************************************/
void CameraMovingState::SetTargetPosition(const glm::vec3& aTarget)
{
  mTargetPosition = aTarget;

  // Take the zoom value into account.
  auto camera = GetCamera();
  if(camera != nullptr)
  {
    auto cameraBehaviorComponent = camera->GetFirstComponentOfType<CameraBehaviorComponent>();
    if(cameraBehaviorComponent != nullptr)
    {
      auto zoomedOut = cameraBehaviorComponent->IsZoomedOut();

      if(zoomedOut)
      {
        mTargetPosition.y += 2.5;
        mTargetPosition.z += 2.5;
      }
    }
  }

  mMoving = true;
}
