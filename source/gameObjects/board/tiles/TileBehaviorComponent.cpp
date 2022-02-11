#include "TileBehaviorComponent.hpp"

using Barebones::TileBehaviorComponent;

/******************************************************************************/
TileBehaviorComponent::TileBehaviorComponent()
  : Component()
  , mHighlightColor(1.0, 1.0, 1.0)
  , mHoverColor(0.1, 0.1, 0.1)
  , mHighlighted(false)
{
}

/******************************************************************************/
void TileBehaviorComponent::SetHighlighted(bool aHighlight)
{
  mHighlighted = aHighlight;
  HandleHighlightChanged(mHighlighted);
}

/******************************************************************************/
void TileBehaviorComponent::SetHighlightColor(const glm::vec3& aColor)
{
  mHighlightColor = aColor;
  HandleHighlightChanged(mHighlighted);
}

/******************************************************************************/
void TileBehaviorComponent::SetHovered(bool aHover)
{
  mHovered = aHover;
  HandleHoverChanged(mHovered);
}
