#include "CameraBehaviorComponent.hpp"

#include <GameObject.hpp>

#include "Signals.hpp"

#include "BoardLayoutComponent.hpp"
#include "BoardTurnManagerComponent.hpp"

#include "CameraDefaultState.hpp"
#include "CameraObservingBoardState.hpp"

using Barebones::CameraBehaviorComponent;

/******************************************************************************/
CameraBehaviorComponent::CameraBehaviorComponent()
  : Component()
  , mFollowedBoard(nullptr)
  , mState(nullptr)
  , mRotation(-40.0)
  , mZoomDistance(0.0)
{
  UrsineEngine::ObjectMoved.Connect(*this, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectMoved(aObject);
  });

  BoardFocusedTileChanged.Connect(*this, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleBoardFocusedTileChanged(aBoard);
  });

  PlayerTurnBegan.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnBegan(aPlayer);
  });

  PlayerTurnEnded.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnEnded(aPlayer);
  });

  CharacterTurnBegan.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterTurnBegan(aCharacter);
  });

  CharacterTurnEnded.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterTurnEnded(aCharacter);
  });

  CameraZoomChangeRequested.Connect(*this, [this](double aZoom)
  {
    this->HandleCameraZoomChangeRequested(aZoom);
  });

  ActDisplayFinished.Connect(*this, [this](UrsineEngine::GameObject& aDisplay)
  {
    this->HandleActDisplayFinished(aDisplay);
  });
}

/******************************************************************************/
void CameraBehaviorComponent::Initialize()
{
  // Begin in the default camera state.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    mState = std::make_unique<CameraDefaultState>(*parent);

    // Initialize the camera rotation.
    parent->SetRotation(mRotation,
                        glm::vec3(1.0, 0.0, 0.0));

    // Initialize the camera position.
    parent->SetPosition(glm::vec3(0.0, 15.0, 0.0));
  }
}

/******************************************************************************/
void CameraBehaviorComponent::Update(double aTime)
{
  if(mState != nullptr)
  {
    auto newState = mState->Update(aTime);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::SetFollowedBoard(UrsineEngine::GameObject& aBoard)
{
  mFollowedBoard = &aBoard;

  // Position the camera to be centered horizontally high above the board.
  auto parent = GetParent();
  auto boardLayoutComponent = mFollowedBoard->GetFirstComponentOfType<BoardLayoutComponent>();
  if(parent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto centerColumn = boardLayoutComponent->GetColumns() / 2;
    auto tile = boardLayoutComponent->GetTileAtLocation(TileLocation(centerColumn, 0));
    if(tile != nullptr)
    {
      auto parentPos = parent->GetPosition();
      parentPos.x = tile->GetPosition().x;
      parent->SetPosition(parentPos);
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandleObjectMoved(UrsineEngine::GameObject* aObject)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleObjectMoved(aObject);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleBoardFocusedTileChanged(aBoard);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandlePlayerTurnBegan(aPlayer);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandlePlayerTurnEnded(aPlayer);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleCharacterTurnBegan(aCharacter);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleCharacterTurnEnded(aCharacter);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandleCameraZoomChangeRequested(double aZoom)
{
  mZoomDistance = aZoom;

  if(mState != nullptr)
  {
    auto newState = mState->HandleCameraZoomChanged(mZoomDistance);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandleActDisplayFinished(UrsineEngine::GameObject& aDisplay)
{
  auto parent = GetParent();
  if(mFollowedBoard != nullptr &&
     parent != nullptr)
  {
    // Swap to the observing board state.
    mState = std::make_unique<CameraObservingBoardState>(*parent, *mFollowedBoard);
  }
}
