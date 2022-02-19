#include "BoardTurnManagerComponent.hpp"

#include <GameObject.hpp>

using Barebones::BoardTurnManagerComponent;

/******************************************************************************/
BoardTurnManagerComponent::BoardTurnManagerComponent()
  : Component()
{
}

/******************************************************************************/
void BoardTurnManagerComponent::Start()
{
  auto parent = GetParent();
  if(!mTurnTracker.empty() &&
     parent != nullptr)
  {
    mTurnTracker.front()->TakeTurn(*parent);
  }
}

/******************************************************************************/
void BoardTurnManagerComponent::AddPlayer(std::unique_ptr<UrsineEngine::GameObject> aPlayer)
{
  auto parent = GetParent();
  auto playerBehaviorComponent = aPlayer->GetFirstComponentOfType<PlayerBehaviorComponent>();
  if(parent != nullptr &&
     playerBehaviorComponent != nullptr)
  {
    // Add the player as a child GameObject.
    parent->AddChild(std::move(aPlayer));

    // Add a turn for the new player to the end of the turn tracker.
    playerBehaviorComponent = parent->GetChildren().back()->GetFirstComponentOfType<PlayerBehaviorComponent>();
    mTurnTracker.emplace_back(playerBehaviorComponent);
  }
}

/******************************************************************************/
void BoardTurnManagerComponent::HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer)
{
  if(!mTurnTracker.empty())
  {
    if(&aPlayer == mTurnTracker.front())
    {
      // Add a copy of this player to the end of the turns list.
      mTurnTracker.emplace_back(&aPlayer);

      // Remove the player at the front of the turns list.
      mTurnTracker.erase(mTurnTracker.begin());

      // Finally, tell the next player to take their turn.
      auto parent = GetParent();
      if(parent != nullptr)
      {
        mTurnTracker.front()->TakeTurn(*parent);
      }
    }
  }
}
