#include "ActionBehaviorComponent.hpp"

using Barebones::ActionBehaviorComponent;

/******************************************************************************/
ActionBehaviorComponent::ActionBehaviorComponent()
  : Component()
  , mSelected(false)
{
}

/******************************************************************************/
void ActionBehaviorComponent::SetHovered(bool aHovered)
{
  mHovered = aHovered;
  HandleHoveredStatusChanged();
}

/******************************************************************************/
void ActionBehaviorComponent::SetSelected(bool aSelected)
{
  mSelected = aSelected;
  HandleSelectionStatusChanged();
}
