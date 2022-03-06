#include "HumanPlayerInputComponent.hpp"

#include "HumanPlayerDefaultInputState.hpp"

#include "CharacterSkillComponent.hpp"

using Barebones::HumanPlayerInputComponent;

/******************************************************************************/
HumanPlayerInputComponent::HumanPlayerInputComponent()
  : InputComponent()
  , mBoard(nullptr)
  , mState(nullptr)
  , mEnabled(false)
{
  SkillSelected.Connect(*this, [this](CharacterSkillComponent& aSkill)
  {
    this->HandleSkillSelected(aSkill);
  });
}

/******************************************************************************/
void HumanPlayerInputComponent::SetBoard(UrsineEngine::GameObject& aBoard)
{
  mBoard = &aBoard;
  if(mState != nullptr)
  {
    mState->SetBoard(*mBoard);
  }
}

/******************************************************************************/
void HumanPlayerInputComponent::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                 int aMods)
{
  if(mState != nullptr &&
     mEnabled)
  {
    auto newState = mState->HandleKeyPressed(aCode,
                                             aMods);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void HumanPlayerInputComponent::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                  int aMods)
{
  if(mState != nullptr &&
     mEnabled)
  {
    auto newState = mState->HandleKeyRepeated(aCode,
                                              aMods);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void HumanPlayerInputComponent::ProtectedInitialize()
{
  // Initialize the player in the default state.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    mState = std::make_unique<HumanPlayerDefaultInputState>(*parent);
  }
}

/******************************************************************************/
void HumanPlayerInputComponent::HandleSkillSelected(CharacterSkillComponent& aSkill)
{
  if(mState != nullptr &&
     mEnabled)
  {
    auto newState = mState->HandleSkillSelected(aSkill);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}
