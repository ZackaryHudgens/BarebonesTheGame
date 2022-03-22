#include "PlayerBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::PlayerBehaviorComponent;

/******************************************************************************/
PlayerBehaviorComponent::PlayerBehaviorComponent()
  : Component()
{
}

/******************************************************************************/
void PlayerBehaviorComponent::TakeTurn(UrsineEngine::GameObject& aBoard)
{
  PlayerTurnBegan.Notify(*this);
  ProtectedTakeTurn(aBoard);
}

/******************************************************************************/
void PlayerBehaviorComponent::EndTurn()
{
  ProtectedEndTurn();
  PlayerTurnEnded.Notify(*this);
}
