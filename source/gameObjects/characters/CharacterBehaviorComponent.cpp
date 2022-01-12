#include "CharacterBehaviorComponent.hpp"

using Barebones::CharacterBehaviorComponent;

/******************************************************************************/
CharacterBehaviorComponent::CharacterBehaviorComponent()
  : Component()
  , mHorizontalDistance(0)
  , mVerticalDistance(0)
  , mDiagonalDistance(0)
  , mSelected(false)
{
}

/******************************************************************************/
void CharacterBehaviorComponent::SetSelected(bool aSelected)
{
  mSelected = aSelected;
  HandleSelectionChanged(aSelected);
  CharacterSelected.Notify(*this);
}

/******************************************************************************/
Barebones::CharacterSelectedSignal Barebones::CharacterSelected;
