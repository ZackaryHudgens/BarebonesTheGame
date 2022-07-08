#include "HumanPlayerBehaviorComponent.hpp"

#include <algorithm>
#include <sstream>

#include <Environment.hpp>

#include "HumanPlayerInitialBehaviorState.hpp"

#include "HumanPlayerInputComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "MenuFactory.hpp"
#include "RewardsMenuLayoutComponent.hpp"

#include "Signals.hpp"

using Barebones::HumanPlayerBehaviorComponent;

/******************************************************************************/
HumanPlayerBehaviorComponent::HumanPlayerBehaviorComponent()
  : PlayerBehaviorComponent()
  , mState(nullptr)
  , mMaxSkeletons(7)
{
  SetSide(Side::ePLAYER);

  CharacterFinishedSpawning.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedSpawning(aCharacter);
  });

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

  SkillCancelled.Connect(*this, [this](Skill& aSkill)
  {
    this->HandleSkillCancelled(aSkill);
  });

  AllCharactersOfSideDefeated.Connect(*this, [this](UrsineEngine::GameObject& aBoard,
                                                    const Side& aSide)
  {
    this->HandleAllCharactersOfSideDefeated(aBoard, aSide);
  });
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::Initialize()
{
  // Begin in the initial state.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    mState = std::make_unique<HumanPlayerInitialBehaviorState>(*parent);
    mState->OnEnter();
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::ProtectedTakeTurn()
{
  auto board = GetBoard();
  if(board != nullptr)
  {
    // Enable the input component.
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto inputComponent = parent->GetFirstComponentOfType<HumanPlayerInputComponent>();
      if(inputComponent != nullptr)
      {
        inputComponent->SetEnabled(true);
        inputComponent->SetBoard(*board);
      }
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
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterFinishedSpawning(CharacterBehaviorComponent& aCharacter)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleCharacterFinishedSpawning(aCharacter);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterStartedMovingAlongPath(CharacterBehaviorComponent& aCharacter)
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

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterFinishedMovingAlongPath(CharacterBehaviorComponent& aCharacter)
{
  // Enable the input component now that a character has stopped moving.
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

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterSelectedFromRewardsMenu(const CharacterType& aType)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleCharacterSelectedFromRewardsMenu(aType);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleSkillExecuted(Skill& aSkill)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleSkillExecuted(aSkill);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleSkillCancelled(Skill& aSkill)
{
  if(mState != nullptr)
  {
    auto newState = mState->HandleSkillCancelled(aSkill);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleAllCharactersOfSideDefeated(UrsineEngine::GameObject& aBoard,
                                                                     const Side& aSide)
{
  auto board = GetBoard();
  if(board != nullptr)
  {
    if(&aBoard == board)
    {
      switch(aSide)
      {
        case Side::eENEMY:
        {
          // If all enemies were defeated, create a rewards menu.
          auto scene = env.GetCurrentScene();
          if(scene != nullptr)
          {
            auto rewardsMenu = MenuFactory::CreateMenu(MenuType::eREWARDS, "rewardsMenu");
            auto menuLayoutComponent = rewardsMenu->GetFirstComponentOfType<RewardsMenuLayoutComponent>();
            menuLayoutComponent->CreateActionForCharacterType(CharacterType::eBASIC_SKELETON);
            menuLayoutComponent->CreateActionForCharacterType(CharacterType::eBONE_THROWER);
            menuLayoutComponent->CreateActionForCharacterType(CharacterType::eCORRUPTED_FARMER);

            // If there are too many skeletons on the board, display a warning that
            // the player will have to get rid of a skeleton before adding another.
            auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
            if(boardLayoutComponent != nullptr)
            {
              auto skeletons = boardLayoutComponent->GetCharactersOfType(Type::eSKELETON);
              if(skeletons.size() >= mMaxSkeletons)
              {
                menuLayoutComponent->SetShowMaxSizeWarning(true);
              }
            }

            scene->AddObject(std::move(rewardsMenu));
          }

          break;
        }
        default:
        {
          break;
        }
      }
    }
  }
}
