#include "CameraBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

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
void CameraBehaviorComponent::CenterOnBoard(UrsineEngine::GameObject& aObject)
{
  auto layout = aObject.GetFirstComponentOfType<BoardLayoutComponent>();
  if(layout != nullptr)
  {
    // Calculate the horizontal center of the board in world space.
    double tileSpacing = layout->GetTileSpacing();
    int columns = layout->GetColumns();

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
