#include "CameraBehaviorComponent.hpp"

#include <GameObject.hpp>

#include "Signals.hpp"

#include "BoardLayoutComponent.hpp"
#include "BoardTurnManagerComponent.hpp"

#include "CameraInitialState.hpp"

#include <iostream>

using Barebones::CameraBehaviorComponent;

/******************************************************************************/
CameraBehaviorComponent::CameraBehaviorComponent()
  : Component()
  , mFollowedBoard(nullptr)
  , mState(nullptr)
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
  // Begin in the initial camera state.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    mState = std::make_unique<CameraInitialState>(*parent);
    mState->OnEnter();
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
