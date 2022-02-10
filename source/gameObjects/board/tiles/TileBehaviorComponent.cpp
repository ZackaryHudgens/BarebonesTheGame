#include "TileBehaviorComponent.hpp"

using Barebones::TileBehaviorComponent;

/******************************************************************************/
TileBehaviorComponent::TileBehaviorComponent()
  : Component()
  , mHighlightColor(1.0, 1.0, 1.0)
  , mHighlighted(false)
{
}

/******************************************************************************/
void TileBehaviorComponent::SetHighlighted(bool aHighlight,
                                           const glm::vec3& aColor)
{
  mHighlighted = aHighlight;
  mHighlightColor = aColor;
  HandleHighlightChanged();
}
