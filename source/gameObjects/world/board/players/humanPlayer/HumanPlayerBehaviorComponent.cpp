#include "HumanPlayerBehaviorComponent.hpp"

#include <sstream>

#include "HumanPlayerInputComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "Signals.hpp"

using Barebones::HumanPlayerBehaviorComponent;

/******************************************************************************/
HumanPlayerBehaviorComponent::HumanPlayerBehaviorComponent()
  : PlayerBehaviorComponent()
  , mBoard(nullptr)
  , mLocation(0, 0)
  , mMaxSkeletons(7)
  , mWaitingForCharacterRemoval(false)
  , mWaitingToSelectCreateSkill(false)
{
  SetSide(Side::ePLAYER);
  mRemoveSkill.SetCharacterType(Type::eSKELETON);

  CharacterStartedMovingAlongPath.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterStartedMovingAlongPath(aCharacter);
  });

  CharacterFinishedMovingAlongPath.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedMovingAlongPath(aCharacter);
  });

  CharacterSelectedFromRewardsMenu.Connect(*this, [this](const CharacterType& aType)
  {
    this->HandleCharacterSelectedFromRewardsMenu(aType);
  });

  SkillExecuted.Connect(*this, [this](Skill& aSkill)
  {
    this->HandleSkillExecuted(aSkill);
  });
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::Update(double aTime)
{
  if(mWaitingToSelectCreateSkill)
  {
    if(mBoard != nullptr)
    {
      mCreateSkill.Select(*mBoard);
    }

    mWaitingToSelectCreateSkill = false;
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::SetLocation(const TileLocation& aLocation)
{
  mLocation = aLocation;
  HumanPlayerMoved.Notify(*this);
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::ProtectedTakeTurn(UrsineEngine::GameObject& aBoard)
{
  // Enable the input component.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto inputComponent = parent->GetFirstComponentOfType<HumanPlayerInputComponent>();
    if(inputComponent != nullptr)
    {
      inputComponent->SetEnabled(true);
      inputComponent->SetBoard(aBoard);

      mBoard = &aBoard;
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::ProtectedEndTurn()
{
  // Disable the input component.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto inputComponent = parent->GetFirstComponentOfType<HumanPlayerInputComponent>();
    if(inputComponent != nullptr)
    {
      inputComponent->SetEnabled(false);
      mBoard = nullptr;
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterStartedMovingAlongPath(CharacterBehaviorComponent& aCharacter)
{
  if(mBoard != nullptr)
  {
    // Disable the input component while a character is moving.
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto inputComponent = parent->GetFirstComponentOfType<HumanPlayerInputComponent>();
      if(inputComponent != nullptr)
      {
        inputComponent->SetEnabled(false);
      }
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterFinishedMovingAlongPath(CharacterBehaviorComponent& aCharacter)
{
  if(mBoard != nullptr)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto inputComponent = parent->GetFirstComponentOfType<HumanPlayerInputComponent>();
      if(inputComponent != nullptr)
      {
        inputComponent->SetEnabled(true);
      }
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterSelectedFromRewardsMenu(const CharacterType& aType)
{
  mCreateSkill.SetCharacterType(aType);

  if(mBoard != nullptr)
  {
    auto boardLayoutComponent = mBoard->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      auto characters = boardLayoutComponent->GetCharactersOfType(Type::eSKELETON);
      if(characters.size() >= mMaxSkeletons)
      {
        mRemoveSkill.Select(*mBoard);
        mWaitingForCharacterRemoval = true;
      }
      else
      {
        mCreateSkill.Select(*mBoard);
      }
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleSkillExecuted(Skill& aSkill)
{
  if(mWaitingForCharacterRemoval)
  {
    if(mBoard != nullptr)
    {
      mWaitingForCharacterRemoval = false;
      mWaitingToSelectCreateSkill = true;
    }
  }
}
