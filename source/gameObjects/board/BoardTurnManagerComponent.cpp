#include "BoardTurnManagerComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

using Barebones::BoardTurnManagerComponent;

/******************************************************************************/
BoardTurnManagerComponent::BoardTurnManagerComponent()
  : Component()
  , mTurnDisplay(nullptr)
  , mWaitingForDisplay(false)
  , mWaitingToTakeTurn(false)
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
void BoardTurnManagerComponent::Update()
{
  // "mWaitingToTakeTurn" is used as a one-frame buffer between the turn display
  // finishing its animation and the front player taking a turn. This way,
  // if the player ends their turn in the same frame they started it, the turn
  // display has already been deleted and nothing breaks.
  if(mWaitingToTakeTurn &&
     !mTurnTracker.empty())
  {
    mWaitingToTakeTurn = false;
    mTurnTracker.front()->TakeTurn();
  }
}

/******************************************************************************/
void BoardTurnManagerComponent::Start()
{
  if(!mTurnTracker.empty())
  {
    // Create a turn display and add it to the canvas.
    CreateTurnDisplay();

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
void BoardTurnManagerComponent::CreateTurnDisplay()
{
  auto scene = env.GetCurrentScene();
  if(scene != nullptr)
  {
    auto canvas = scene->GetCanvas();
    if(canvas != nullptr)
    {
      // Create a turn display and add it to the canvas.
      auto turnDisplay = std::make_unique<UrsineEngine::GameObject>("turnDisplay");
      turnDisplay->AddComponent(std::make_unique<TurnDisplayComponent>());
      canvas->AddChild(std::move(turnDisplay));

      // Keep a reference to the current turn display.
      mTurnDisplay = canvas->GetChildren().back()->GetFirstComponentOfType<TurnDisplayComponent>();
    }
  }
}

/******************************************************************************/
void BoardTurnManagerComponent::HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer)
{
  // Create a new turn display.
  CreateTurnDisplay();

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
      mTurnDisplay = nullptr;
      mWaitingForDisplay = false;
      mWaitingToTakeTurn = true;
    }
  }
}

/******************************************************************************/
Barebones::PlayerTurnBeganSignal Barebones::PlayerTurnBegan;
Barebones::PlayerTurnEndedSignal Barebones::PlayerTurnEnded;
