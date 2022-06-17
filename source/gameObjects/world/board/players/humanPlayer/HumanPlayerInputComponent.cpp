#include "HumanPlayerInputComponent.hpp"

#include "Signals.hpp"

#include "PlayerBehaviorComponent.hpp"
#include "BoardLayoutComponent.hpp"

#include "HumanPlayerDefaultInputState.hpp"
#include "HumanPlayerUsingSkillInputState.hpp"
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
    auto playerBehaviorComponent = parent->GetFirstComponentOfType<PlayerBehaviorComponent>();
    auto boardLayoutComponent = mBoard->GetFirstComponentOfType<BoardLayoutComponent>();
    if(playerBehaviorComponent != nullptr &&
       boardLayoutComponent != nullptr)
    {
      // If there are too many characters on the board under the player's control,
      // then a removal of one of them is required before a new one can be added.
      bool removalRequired = false;
      auto controlledSide = playerBehaviorComponent->GetSide();
      auto charactersOnSide = boardLayoutComponent->GetCharactersOnSide(controlledSide);
      if(charactersOnSide.size() >= 5)
      {
        removalRequired = true;
      }

      mState = std::make_unique<HumanPlayerPlacingCharacterInputState>(*parent,
                                                                       aType,
                                                                       removalRequired);
      mState->SetBoard(*mBoard);
    }
  }
}
