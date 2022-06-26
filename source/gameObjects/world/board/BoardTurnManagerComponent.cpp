#include "BoardTurnManagerComponent.hpp"

#include <sstream>

#include <CoreSignals.hpp>
#include <Environment.hpp>
#include <GameObject.hpp>

#include "Fonts.hpp"
#include "Signals.hpp"

#include "PlayerBehaviorComponent.hpp"

#include "ScrollingMessageBehaviorComponent.hpp"

using Barebones::BoardTurnManagerComponent;

/******************************************************************************/
BoardTurnManagerComponent::BoardTurnManagerComponent()
  : Component()
  , mTurnDisplay(nullptr)
{
  PlayerTurnEnded.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnEnded(aPlayer);
  });

  BoardReadyForUse.Connect(*this, [this](UrsineEngine::GameObject& aBoard)
  {
    //this->HandleBoardReadyForUse(aBoard);
  });

  UrsineEngine::ObjectPendingDeletion.Connect(*this, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectPendingDeletion(aObject);
  });
}

/******************************************************************************/
void BoardTurnManagerComponent::Update(double aTime)
{
  // "mWaitingToTakeTurn" is used as a one-frame buffer between the turn display
  // finishing its animation and the front player taking a turn. This way,
  // if the player ends their turn in the same frame they started it, the turn
  // display has already been deleted and nothing breaks.
  if(mWaitingToTakeTurn &&
     !mTurnTracker.empty())
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      mWaitingToTakeTurn = false;

      auto player = GetCurrentPlayer();
      if(player != nullptr)
      {
        auto playerBehaviorComponent = player->GetFirstComponentOfType<PlayerBehaviorComponent>();
        if(playerBehaviorComponent != nullptr)
        {
          auto parent = GetParent();
          if(parent != nullptr)
          {
            playerBehaviorComponent->TakeTurn(*parent);
          }
        }
      }
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
    mTurnTracker.emplace_back(parent->GetChildren().back());
  }
}

/******************************************************************************/
UrsineEngine::GameObject* BoardTurnManagerComponent::GetCurrentPlayer()
{
  UrsineEngine::GameObject* player = nullptr;

  if(!mTurnTracker.empty())
  {
    player = mTurnTracker.front();
  }

  return player;
}

/******************************************************************************/
void BoardTurnManagerComponent::CreateTurnDisplay()
{
  auto scene = env.GetCurrentScene();
  if(scene != nullptr)
  {
    auto foreground = scene->GetForeground();
    if(foreground != nullptr)
    {
      auto currentPlayer = GetCurrentPlayer();
      if(currentPlayer != nullptr)
      {
        // Create a turn display and add it to the foreground.
        auto turnDisplay = std::make_unique<UrsineEngine::GameObject>("turnDisplay");

        std::stringstream message;
        message << currentPlayer->GetName() << "'s Turn";
        turnDisplay->AddComponent(std::make_unique<ScrollingMessageBehaviorComponent>(message.str(),
                                                                                      BIGGEST_FONT_SIZE,
                                                                                      200.0));
        if(foreground->AddChild(std::move(turnDisplay)))
        {
          // Keep a reference to the current turn display.
          mTurnDisplay = foreground->GetChildren().back();
        }
      }
    }
  }
}

/******************************************************************************/
void BoardTurnManagerComponent::HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer)
{
  // First, add a copy of the current player to the end of the turns list.
  mTurnTracker.emplace_back(mTurnTracker.front());

  // Then remove the instance of the current player in the front of the turns list.
  mTurnTracker.erase(mTurnTracker.begin());

  // Create a new turn display.
  CreateTurnDisplay();
}

/******************************************************************************/
void BoardTurnManagerComponent::HandleBoardReadyForUse(UrsineEngine::GameObject& aBoard)
{
  if(&aBoard == GetParent())
  {
    // When the board is ready, create a turn display. When the turn display
    // finishes, the player in the front of the turn tracker will take a turn.
    CreateTurnDisplay();
  }
}

/******************************************************************************/
void BoardTurnManagerComponent::HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject)
{
  if(aObject == mTurnDisplay)
  {
    mTurnDisplay = nullptr;

    // The turn display has finished its animation, so the player in front
    // of the turn tracker should take a turn on the next Update().
    mWaitingToTakeTurn = true;
  }
}
