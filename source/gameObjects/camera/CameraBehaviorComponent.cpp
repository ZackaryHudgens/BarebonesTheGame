#include "CameraBehaviorComponent.hpp"

#include <GameObject.hpp>

#include "BoardTurnManagerComponent.hpp"

using Barebones::CameraBehaviorComponent;

/******************************************************************************/
CameraBehaviorComponent::CameraBehaviorComponent()
  : Component()
  , mFollowedBoard(nullptr)
  , mTargetPosition(0.0, 0.0, 0.0)
  , mYDistance(5.0)
  , mZDistance(5.0)
  , mRotation(-40.0)
  , mSpeed(0.3)
  , mMoving(false)
{
  PlayerMoved.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerMoved(aPlayer);
  });

  PlayerTurnBegan.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnBegan(aPlayer);
  });
}

/******************************************************************************/
void CameraBehaviorComponent::Initialize()
{
  // Initialize the camera position and orientation.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->SetPosition(glm::vec3(0.0,
                                  mYDistance,
                                  mZDistance));
    parent->SetRotation(mRotation, glm::vec3(1.0,
                                             0.0,
                                             0.0));
  }
}

/******************************************************************************/
void CameraBehaviorComponent::Update()
{
  if(mMoving)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto position = glm::mix(parent->GetPosition(),
                               mTargetPosition,
                               mSpeed);

      // If the position is close enough to the target position,
      // move directly to the target position and stop moving.
      if(std::abs(mTargetPosition.x - position.x) <= 0.005 &&
         std::abs(mTargetPosition.y - position.y) <= 0.005 &&
         std::abs(mTargetPosition.z - position.z) <= 0.005)
      {
        parent->SetPosition(mTargetPosition);
        mMoving = false;
      }
      else
      {
        parent->SetPosition(position);
      }
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::FollowBoard(UrsineEngine::GameObject& aBoard)
{
  mFollowedBoard = &aBoard;

  auto turnManager = aBoard.GetFirstComponentOfType<BoardTurnManagerComponent>();
  if(turnManager != nullptr)
  {
    auto player = turnManager->GetCurrentPlayer();
    if(player != nullptr)
    {
      auto playerBehaviorComponent = player->GetFirstComponentOfType<PlayerBehaviorComponent>();
      if(playerBehaviorComponent != nullptr)
      {
        HandlePlayerMoved(*playerBehaviorComponent);
      }
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandlePlayerMoved(PlayerBehaviorComponent& aPlayer)
{
  if(mFollowedBoard != nullptr)
  {
    auto turnManager = mFollowedBoard->GetFirstComponentOfType<BoardTurnManagerComponent>();
    if(turnManager != nullptr)
    {
      // Only move the camera if the player that moved is the current player
      // on the board.
      if(aPlayer.GetParent() == turnManager->GetCurrentPlayer())
      {
        auto boardLayoutComponent = mFollowedBoard->GetFirstComponentOfType<BoardLayoutComponent>();
        if(boardLayoutComponent != nullptr)
        {
          auto tile = boardLayoutComponent->GetTileAtLocation(aPlayer.GetLocation());
          auto parent = GetParent();
          if(tile != nullptr &&
             parent != nullptr)
          {
            // Calculate the new position for the camera.
            auto newPos = tile->GetPosition();
            newPos.y += mYDistance;
            newPos.z += mZDistance;

            mTargetPosition = newPos;
            mMoving = true;
          }
        }
      }
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  HandlePlayerMoved(aPlayer);
}
