#include "TileBehaviorComponent.hpp"

using Barebones::TileBehaviorComponent;

/******************************************************************************/
TileBehaviorComponent::TileBehaviorComponent()
  : Component()
  , mHighlighted(false)
{
}

/******************************************************************************/
void TileBehaviorComponent::SetHighlighted(bool aHighlighted)
{
  mHighlighted = aHighlighted;
  HandleHighlightChanged(aHighlighted);
}
