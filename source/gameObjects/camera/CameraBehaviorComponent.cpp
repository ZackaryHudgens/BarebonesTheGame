#include "CameraBehaviorComponent.hpp"

#include "BoardBehaviorComponent.hpp"

using Barebones::CameraBehaviorComponent;

/******************************************************************************/
CameraBehaviorComponent::CameraBehaviorComponent()
  : Component()
  , mHeight(6.0)
  , mZDistance(5.0)
  , mRotation(-40.0)
{
}

/******************************************************************************/
void CameraBehaviorComponent::FollowBoard(UrsineEngine::GameObject& aObject)
{
  auto boardComp = aObject.GetFirstComponentOfType<BoardBehaviorComponent>();
  if(boardComp != nullptr)
  {
    // Calculate the horizontal center of the board in world space.
    double tileSpacing = boardComp->GetTileSpacing();
    int columns = boardComp->GetColumns();

    double boardWidth = (double)columns + ((columns - 1) * tileSpacing);
    double distanceToCenter = (boardWidth / 2.0) - 0.5;

    double horizontalCenter = aObject.GetPosition().x + distanceToCenter;

    auto parent = GetParent();
    if(parent != nullptr)
    {
      parent->SetPosition(glm::vec3(horizontalCenter,
                                    mHeight,
                                    mZDistance));

      parent->SetRotation(mRotation, glm::vec3(1.0,
                                               0.0,
                                               0.0));
    }
  }
}
