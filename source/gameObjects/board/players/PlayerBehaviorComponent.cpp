#include "PlayerBehaviorComponent.hpp"

#include "BoardTurnManagerComponent.hpp"

using Barebones::PlayerBehaviorComponent;

/******************************************************************************/
PlayerBehaviorComponent::PlayerBehaviorComponent()
  : Component()
{
}

/******************************************************************************/
void PlayerBehaviorComponent::TakeTurn()
{
  ProtectedTakeTurn();
  PlayerTurnBegan.Notify(*this);
}

/******************************************************************************/
void PlayerBehaviorComponent::EndTurn()
{
  ProtectedEndTurn();
  PlayerTurnEnded.Notify(*this);
}
