#include "CameraBehaviorComponent.hpp"

#include <GameObject.hpp>

using Barebones::CameraBehaviorComponent;

/******************************************************************************/
CameraBehaviorComponent::CameraBehaviorComponent()
  : Component()
  , mYDistance(5.0)
  , mZDistance(5.0)
  , mRotation(-40.0)
  , mSpeed(0.3)
  , mMoving(false)
{
  TileHovered.Connect(*this, [this](TileBehaviorComponent& aTile)
  {
    this->HandleTileHovered(aTile);
  });
}

/******************************************************************************/
void CameraBehaviorComponent::Update()
{
  if(mMoving)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto position = glm::mix(parent->GetPosition(),
                               mTargetPosition,
                               mSpeed);

      // If the position is close enough to the target position,
      // move directly to the target position and stop moving.
      if(std::abs(mTargetPosition.x - position.x) <= 0.05 &&
         std::abs(mTargetPosition.y - position.y) <= 0.05 &&
         std::abs(mTargetPosition.z - position.z) <= 0.05)
      {
        parent->SetPosition(mTargetPosition);
        mMoving = false;
      }
      else
      {
        parent->SetPosition(position);
      }
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::Initialize()
{
  // Initialize the camera position and orientation.
  auto cameraParent = GetParent();
  if(cameraParent != nullptr)
  {
    cameraParent->SetPosition(glm::vec3(0.0,
                                        mYDistance,
                                        mZDistance));
    cameraParent->SetRotation(mRotation, glm::vec3(1.0,
                                                   0.0,
                                                   0.0));
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandleTileHovered(TileBehaviorComponent& aTile)
{
  auto cameraParent = GetParent();
  auto tileParent = aTile.GetParent();
  if(cameraParent != nullptr &&
     tileParent != nullptr)
  {
    // Calculate the new position for the camera.
    auto newPos = tileParent->GetPosition();
    newPos.y += mYDistance;
    newPos.z += mZDistance;

    mTargetPosition = newPos;
    mMoving = true;
  }
}
