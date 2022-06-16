#include "HumanPlayerInputComponent.hpp"

#include "Signals.hpp"

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerDefaultInputState.hpp"
#include "HumanPlayerUsingSkillInputState.hpp"
#include "HumanPlayerRemovingCharacterInputState.hpp"
#include "HumanPlayerPlacingCharacterInputState.hpp"

using Barebones::HumanPlayerInputComponent;

/******************************************************************************/
HumanPlayerInputComponent::HumanPlayerInputComponent()
  : InputComponent()
  , mBoard(nullptr)
  , mState(nullptr)
  , mEnabled(false)
{
  SkillSelected.Connect(*this, [this](Skill& aSkill)
  {
    this->HandleSkillSelected(aSkill);
  });

  CharacterSelectedFromRewardsMenu.Connect(*this, [this](const CharacterType& aType)
  {
    this->HandleCharacterSelectedFromRewardsMenu(aType);
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

  if(mBoard != nullptr)
  {
    mState->SetBoard(*mBoard);
  }
}

/******************************************************************************/
void HumanPlayerInputComponent::HandleSkillSelected(Skill& aSkill)
{
  // When a skill is selected, swap to the Using Skill state.
  auto parent = GetParent();
  if(parent != nullptr &&
     mBoard != nullptr)
  {
    mState = std::make_unique<HumanPlayerUsingSkillInputState>(*parent, aSkill);
    mState->SetBoard(*mBoard);
  }
}

/******************************************************************************/
void HumanPlayerInputComponent::HandleCharacterSelectedFromRewardsMenu(const CharacterType& aType)
{
  auto parent = GetParent();
  if(parent != nullptr &&
     mBoard != nullptr)
  {
    auto boardLayoutComponent = mBoard->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      // If there are too many characters on the board under the player's control,
      // swap to the Removing Character state. Otherwise, swap to the Placing
      // Character state.
      auto charactersOnSide = boardLayoutComponent->GetCharactersOnSide(Side::ePLAYER);
      if(charactersOnSide.size() <= 7)
      {
        mState = std::make_unique<HumanPlayerRemovingCharacterInputState>(*parent);
      }
      else
      {
        mState = std::make_unique<HumanPlayerPlacingCharacterInputState>(*parent, aType);
      }

      mState->SetBoard(*mBoard);
    }
  }
}
