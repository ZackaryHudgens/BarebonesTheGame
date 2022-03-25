#include "CameraBehaviorComponent.hpp"

#include <GameObject.hpp>

#include "Signals.hpp"

#include "BoardTurnManagerComponent.hpp"

#include "CameraDefaultState.hpp"

using Barebones::CameraBehaviorComponent;

/******************************************************************************/
CameraBehaviorComponent::CameraBehaviorComponent()
  : Component()
  , mFollowedBoard(nullptr)
  , mState(nullptr)
{
  UrsineEngine::ObjectMoved.Connect(*this, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectMoved(aObject);
  });

  HumanPlayerMoved.Connect(*this, [this](HumanPlayerBehaviorComponent& aPlayer)
  {
    this->HandleHumanPlayerMoved(aPlayer);
  });

  PlayerTurnBegan.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnBegan(aPlayer);
  });

  CharacterTurnBegan.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterTurnBegan(aCharacter);
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
  }
}

/******************************************************************************/
void CameraBehaviorComponent::Update()
{
  if(mState != nullptr)
  {
    auto newState = mState->Update();
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

  if(mState != nullptr)
  {
    auto newState = mState->HandleBoardFollowed(aBoard);
    if(newState != nullptr)
    {
      mState.swap(newState);
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
void CameraBehaviorComponent::HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleHumanPlayerMoved(aPlayer);
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
