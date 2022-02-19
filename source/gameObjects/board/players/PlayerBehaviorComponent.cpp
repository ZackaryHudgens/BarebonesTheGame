#include "PlayerBehaviorComponent.hpp"

#include <iostream>

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

/******************************************************************************/
Barebones::PlayerTurnBeganSignal   Barebones::PlayerTurnBegan;
Barebones::PlayerTurnEndedSignal   Barebones::PlayerTurnEnded;
