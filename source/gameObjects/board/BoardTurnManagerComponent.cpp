#include "BoardTurnManagerComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "TurnDisplayComponent.hpp"

using Barebones::BoardTurnManagerComponent;

/******************************************************************************/
BoardTurnManagerComponent::BoardTurnManagerComponent()
  : Component()
{
  TurnDisplayFinished.Connect(*this, [this]()
  {
    this->HandleTurnDisplayFinished();
  });
}

/******************************************************************************/
void BoardTurnManagerComponent::Start()
{
  if(!mTurnTracker.empty())
  {
    // Create a turn display and add it to the scene. When the turn display
    // is finished, the player in the front of the turn tracker will take their turn.
    auto turnDisplay = std::make_unique<UrsineEngine::GameObject>("turnDisplay");
    turnDisplay->AddComponent(std::make_unique<TurnDisplayComponent>());

    auto scene = env.GetCurrentScene();
    if(scene != nullptr)
    {
      scene->AddObject(std::move(turnDisplay));
    }

    PlayerTurnBegan.Notify(*mTurnTracker.front());
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

      // Finally, tell the turn tracker that the next player
      // is about to begin their turn.
      PlayerTurnBegan.Notify(*mTurnTracker.front());
    }
  }
}

/******************************************************************************/
void BoardTurnManagerComponent::HandleTurnDisplayFinished()
{
  auto parent = GetParent();
  if(!mTurnTracker.empty() &&
     parent != nullptr)
  {
    mTurnTracker.front()->TakeTurn(*parent);
  }
}

/******************************************************************************/
Barebones::PlayerTurnBeganSignal Barebones::PlayerTurnBegan;
Barebones::PlayerTurnEndedSignal Barebones::PlayerTurnEnded;
