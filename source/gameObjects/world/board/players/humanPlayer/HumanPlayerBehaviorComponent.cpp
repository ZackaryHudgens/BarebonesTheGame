#include "HumanPlayerBehaviorComponent.hpp"

#include <algorithm>
#include <sstream>

#include <Environment.hpp>

#include "HumanPlayerInputComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "MenuFactory.hpp"
#include "RewardsMenuLayoutComponent.hpp"

#include "Signals.hpp"

using Barebones::HumanPlayerBehaviorComponent;

/******************************************************************************/
HumanPlayerBehaviorComponent::HumanPlayerBehaviorComponent()
  : PlayerBehaviorComponent()
  , mBoard(nullptr)
  , mMaxSkeletons(7)
  , mWaitingForCharacterRemoval(false)
  , mWaitingToSelectCreateSkill(false)
  , mWaitingForCharacterCreation(false)
{
  SetSide(Side::ePLAYER);
  mRemoveSkill.SetCharacterType(Type::eSKELETON);

  mSkeletonInventory.emplace_back(CharacterType::eBASIC_SKELETON);
  mSkeletonInventory.emplace_back(CharacterType::eBASIC_SKELETON);
  mSkeletonInventory.emplace_back(CharacterType::eBASIC_SKELETON);
  mSkeletonInventory.emplace_back(CharacterType::eBASIC_SKELETON);
  mSkeletonInventory.emplace_back(CharacterType::eBASIC_SKELETON);
  mSkeletonInventory.emplace_back(CharacterType::eBASIC_SKELETON);
  mSkeletonInventory.emplace_back(CharacterType::eBASIC_SKELETON);

  BoardFinishedInitialSequence.Connect(*this, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleBoardFinishedInitialSequence(aBoard);
  });

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
void HumanPlayerBehaviorComponent::Update(double aTime)
{
  if(mWaitingToSelectCreateSkill)
  {
    if(mBoard != nullptr)
    {
      mCreateSkill.Select(*mBoard);
      mWaitingForCharacterCreation = true;
    }

    mWaitingToSelectCreateSkill = false;
  }
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
void HumanPlayerBehaviorComponent::HandleBoardFinishedInitialSequence(UrsineEngine::GameObject& aBoard)
{
  mBoard = &aBoard;

  std::stringstream nameStream;

  // Create a character for each type in our inventory and add them
  // to the board.
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    int row = 0;
    int index = 0;
    for(const auto& characterType : mSkeletonInventory)
    {
      TileLocation location(0, row);

      nameStream << "skeleton_" << index;
      auto character = CharacterFactory::CreateCharacter(characterType, nameStream.str());
      
      boardLayoutComponent->AddCharacterAtLocation(std::move(character), location);
      mSpawningCharacters.emplace_back(boardLayoutComponent->GetCharacterAtLocation(location));

      nameStream.str("");
      ++index;
      ++row;
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleCharacterFinishedSpawning(CharacterBehaviorComponent& aCharacter)
{
  auto characterObject = aCharacter.GetParent();
  if(characterObject != nullptr)
  {
    auto foundCharacter = std::find(mSpawningCharacters.begin(),
                                    mSpawningCharacters.end(),
                                    characterObject);
    if(foundCharacter != mSpawningCharacters.end())
    {
      mSpawningCharacters.erase(foundCharacter);

      if(mSpawningCharacters.empty() &&
         mBoard != nullptr)
      {
        NewEnemyWaveRequested.Notify(*mBoard);
      }
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
  if(&aSkill == &mRemoveSkill &&
     mWaitingForCharacterRemoval)
  {
    mWaitingForCharacterRemoval = false;
    mWaitingToSelectCreateSkill = true;
  }

  if(&aSkill == &mCreateSkill &&
     mWaitingForCharacterCreation)
  {
    mWaitingForCharacterCreation = false;

    if(mBoard != nullptr)
    {
      NewEnemyWaveRequested.Notify(*mBoard);
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleSkillCancelled(Skill& aSkill)
{
  if(&aSkill == &mRemoveSkill &&
     mWaitingForCharacterRemoval)
  {
    mWaitingForCharacterRemoval = false;

    if(mBoard != nullptr)
    {
      NewEnemyWaveRequested.Notify(*mBoard);
    }
  }

  if(&aSkill == &mCreateSkill &&
     mWaitingForCharacterCreation)
  {
    mWaitingForCharacterCreation = false;

    if(mBoard != nullptr)
    {
      NewEnemyWaveRequested.Notify(*mBoard);
    }
  }
}

/******************************************************************************/
void HumanPlayerBehaviorComponent::HandleAllCharactersOfSideDefeated(UrsineEngine::GameObject& aBoard,
                                                                     const Side& aSide)
{
  if(&aBoard == mBoard)
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
          auto boardLayoutComponent = mBoard->GetFirstComponentOfType<BoardLayoutComponent>();
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
