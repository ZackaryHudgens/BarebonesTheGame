#include "CharacterBehaviorComponent.hpp"

using Barebones::CharacterBehaviorComponent;

/******************************************************************************/
CharacterBehaviorComponent::CharacterBehaviorComponent()
  : Component()
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
Barebones::MoveList CharacterBehaviorComponent::GetMovements(const TileLocation& aLocation) const
{
  return MoveList();
}

/******************************************************************************/
Barebones::CharacterSelectedSignal Barebones::CharacterSelected;
