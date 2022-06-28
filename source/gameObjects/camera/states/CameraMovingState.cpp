#include "CameraMovingState.hpp"

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
void CameraMovingState::SetTargetPosition(const glm::vec3& aTarget)
{
  mTargetPosition = aTarget;
  mMoving = true;
}
