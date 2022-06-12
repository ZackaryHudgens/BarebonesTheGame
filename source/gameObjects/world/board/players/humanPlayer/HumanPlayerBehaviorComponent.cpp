#include "HumanPlayerBehaviorComponent.hpp"

#include <sstream>

#include "HumanPlayerInputComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "CharacterFactory.hpp"

#include "Signals.hpp"

using Barebones::HumanPlayerBehaviorComponent;

/******************************************************************************/
HumanPlayerBehaviorComponent::HumanPlayerBehaviorComponent()
  : PlayerBehaviorComponent()
  , mLocation(0, 0)
  , mTakingTurn(false)
{
  SetSide(Side::ePLAYER);

  mCharacterInventory.emplace_back(CharacterType::eBASIC_SKELETON);
  mCharacterInventory.emplace_back(CharacterType::eBASIC_SKELETON);
  mCharacterInventory.emplace_back(CharacterType::eBASIC_SKELETON);
  mCharacterInventory.emplace_back(CharacterType::eBONE_THROWER);
  mCharacterInventory.emplace_back(CharacterType::eBONE_THROWER);
  mCharacterInventory.emplace_back(CharacterType::eBONE_THROWER);

  CharacterStartedMovingAlongPath.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterStartedMovingAlongPath(aCharacter);
  });

  CharacterFinishedMovingAlongPath.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedMovingAlongPath(aCharacter);
  });

  BoardReadyForUse.Connect(*this, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleBoardReadyForUse(aBoard);
  });
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
      mTakingTurn = true;
      inputComponent->SetEnabled(true);
      inputComponent->SetBoard(aBoard);
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
      mTakingTurn = false;
      inputComponent->SetEnabled(false);
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleBoardReadyForUse(UrsineEngine::GameObject& aBoard)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    std::stringstream nameStream;
    int row = 0;
    for(const auto& characterType : mCharacterInventory)
    {
      nameStream << "skeleton" << row;
      boardLayoutComponent->AddCharacterAtLocation(CharacterFactory::CreateCharacter(characterType, nameStream.str()),
                                                   TileLocation(0, row));
      nameStream.str("");
      ++row;
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterStartedMovingAlongPath(CharacterBehaviorComponent& aCharacter)
{
  if(mTakingTurn)
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
  if(mTakingTurn)
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
