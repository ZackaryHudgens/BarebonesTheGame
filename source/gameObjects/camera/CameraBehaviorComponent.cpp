#include "CameraBehaviorComponent.hpp"

#include <GameObject.hpp>

using Barebones::CameraBehaviorComponent;

/******************************************************************************/
CameraBehaviorComponent::CameraBehaviorComponent()
  : Component()
  , mYDistance(5.0)
  , mZDistance(5.0)
  , mRotation(-40.0)
{
  TileHovered.Connect(*this, [this](TileBehaviorComponent& aTile)
  {
    this->HandleTileHovered(aTile);
  });
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

    cameraParent->SetPosition(newPos);
  }
}
