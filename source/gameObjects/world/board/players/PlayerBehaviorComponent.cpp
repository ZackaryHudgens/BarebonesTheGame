#include "PlayerBehaviorComponent.hpp"

#include "Signals.hpp"

#include "BoardTurnManagerComponent.hpp"

using Barebones::PlayerBehaviorComponent;

/******************************************************************************/
PlayerBehaviorComponent::PlayerBehaviorComponent()
  : Component()
  , mLocation(0, 0)
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
void PlayerBehaviorComponent::SetLocation(const TileLocation& aLocation)
{
  mLocation = aLocation;
  PlayerMoved.Notify(*this);
}
