#include "BoardTurnManagerComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

using Barebones::BoardTurnManagerComponent;

/******************************************************************************/
BoardTurnManagerComponent::BoardTurnManagerComponent()
  : Component()
  , mWaitingForDisplay(false)
{
  PlayerTurnEnded.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnEnded(aPlayer);
  });

  TurnDisplayFinished.Connect(*this, [this](TurnDisplayComponent& aDisplay)
  {
    this->HandleTurnDisplayFinished(aDisplay);
  });
}

/******************************************************************************/
void BoardTurnManagerComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a turn display and add it as a child object.
    auto turnDisplay = std::make_unique<UrsineEngine::GameObject>("turnDisplay");
    turnDisplay->AddComponent(std::make_unique<TurnDisplayComponent>());
    turnDisplay->SetPosition(glm::vec3(0.0, 0.0, 0.1));
    parent->AddChild(std::move(turnDisplay));

    mTurnDisplay = parent->GetChildren().back()->GetFirstComponentOfType<TurnDisplayComponent>();
  }
}

/******************************************************************************/
void BoardTurnManagerComponent::Start()
{
  if(!mTurnTracker.empty())
  {
    // Display a message for the current player. When the message stops displaying,
    // the player's turn will begin.
    if(mTurnDisplay != nullptr)
    {
      mTurnDisplay->DisplayMessageForPlayer(*mTurnTracker.front());
      mWaitingForDisplay = true;
    }
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
  if(mTurnDisplay != nullptr)
  {
    // First, add a copy of the current player to the end of the turns list.
    mTurnTracker.emplace_back(mTurnTracker.front());

    // Then remove the instance of the current player in the front of the turns list.
    mTurnTracker.erase(mTurnTracker.begin());

    // Finally, display a message for the next player.
    mTurnDisplay->DisplayMessageForPlayer(*mTurnTracker.front());
    mWaitingForDisplay = true;
  }
}

/******************************************************************************/
void BoardTurnManagerComponent::HandleTurnDisplayFinished(TurnDisplayComponent& aDisplay)
{
  if(mWaitingForDisplay)
  {
    if(!mTurnTracker.empty())
    {
      mWaitingForDisplay = false;

      // Tell the player in front to take their turn.
      mTurnTracker.front()->TakeTurn();
    }
  }
}

/******************************************************************************/
Barebones::PlayerTurnBeganSignal Barebones::PlayerTurnBegan;
Barebones::PlayerTurnEndedSignal Barebones::PlayerTurnEnded;
