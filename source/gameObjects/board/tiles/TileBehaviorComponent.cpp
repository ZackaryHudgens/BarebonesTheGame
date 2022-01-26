#include "TileBehaviorComponent.hpp"

using Barebones::TileBehaviorComponent;

/******************************************************************************/
TileBehaviorComponent::TileBehaviorComponent()
  : Component()
  , mHovered(false)
  , mHilighted(false)
{
}

/******************************************************************************/
void TileBehaviorComponent::SetHovered(bool aHovered)
{
  mHovered = aHovered;
  HandleHoverChanged(aHovered);

  TileHovered.Notify(*this);
}

/******************************************************************************/
void TileBehaviorComponent::SetHighlighted(bool aHighlighted)
{
  mHilighted = aHighlighted;
  HandleHighlightChanged(aHighlighted);
}

/******************************************************************************/
Barebones::TileHoveredSignal Barebones::TileHovered;
