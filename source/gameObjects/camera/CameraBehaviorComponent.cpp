#include "CameraBehaviorComponent.hpp"

#include <GameObject.hpp>

#include "Signals.hpp"

#include "BoardLayoutComponent.hpp"
#include "BoardTurnManagerComponent.hpp"

#include "CameraDefaultState.hpp"

using Barebones::CameraBehaviorComponent;

/******************************************************************************/
CameraBehaviorComponent::CameraBehaviorComponent()
  : Component()
  , mFollowedBoard(nullptr)
  , mState(nullptr)
  , mRotation(-40.0)
  , mZoomDistance(0.0)
{
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
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::SetFollowedBoard(UrsineEngine::GameObject& aBoard)
{
  mFollowedBoard = &aBoard;

  auto boardLayoutComponent = mFollowedBoard->GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    // Get the tile in the center of the board and set the camera position using
    // that tile.
    int centerColumn = boardLayoutComponent->GetColumns() / 2;
    int centerRow = boardLayoutComponent->GetRows() / 2;

    TileLocation centerLocation(centerColumn, centerRow);
    auto tile = boardLayoutComponent->GetTileAtLocation(centerLocation);
    if(tile != nullptr)
    {
      auto tilePos = tile->GetPosition();
      tilePos.y += 15.0;
      tilePos.z += 5.0;

      auto parent = GetParent();
      if(parent != nullptr)
      {
        parent->SetPosition(tilePos);
      }
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
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
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
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
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
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
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
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void CameraBehaviorComponent::HandleCameraZoomChangeRequested(double aZoom)
{
  mZoomDistance = aZoom;
}

/******************************************************************************/
void CameraBehaviorComponent::HandleActDisplayFinished(UrsineEngine::GameObject& aDisplay)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleActDisplayFinished(aDisplay);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}
