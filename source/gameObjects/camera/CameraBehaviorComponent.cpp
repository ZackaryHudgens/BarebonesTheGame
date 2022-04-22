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
  , mRotation(-40.0)
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

  SkillSelectedFromMenu.Connect(*this, [this](Skill& aSkill)
  {
    this->HandleSkillSelectedFromMenu(aSkill);
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
void CameraBehaviorComponent::HandleSkillSelectedFromMenu(Skill& aSkill)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleSkillSelectedFromMenu(aSkill);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}
