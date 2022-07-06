#include "BoardWaveManagerComponent.hpp"

#include <algorithm>
#include <sstream>

#include <Environment.hpp>
#include <Scene.hpp>

#include "BoardLayoutComponent.hpp"
#include "RewardsMenuLayoutComponent.hpp"

#include "CharacterFactory.hpp"
#include "MenuFactory.hpp"

#include "ScrollingMessageBehaviorComponent.hpp"

#include "Signals.hpp"
#include "TileUtil.hpp"
#include "Fonts.hpp"

using Barebones::BoardWaveManagerComponent;

// Initialize the enocunter lists for each act.
std::vector<Barebones::CharacterType> BoardWaveManagerComponent::mActOneEncounters =
  std::vector<Barebones::CharacterType>(
  {
    CharacterType::eCORRUPTED_FARMER
  });
std::vector<Barebones::CharacterType> BoardWaveManagerComponent::mActTwoEncounters =
  std::vector<Barebones::CharacterType>(
  {
    CharacterType::eCORRUPTED_FARMER
  });
std::vector<Barebones::CharacterType> BoardWaveManagerComponent::mActThreeEncounters =
  std::vector<Barebones::CharacterType>(
  {
    CharacterType::eCORRUPTED_FARMER
  });

/******************************************************************************/
BoardWaveManagerComponent::BoardWaveManagerComponent()
  : Component()
  , mAct(Act::eACT_ONE)
  , mWaveDisplay(nullptr)
  , mWaveNumber(0)
  , mWavesBeforeBoss(3)
  , mMinimumEnemies(2)
  , mMaximumEnemies(4)
{
  NewEnemyWaveRequested.Connect(*this, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleNewEnemyWaveRequested(aBoard);
  });

  CharacterFinishedSpawning.Connect(*this, [this](CharacterBehaviorComponent& aCharacter)
  {
    this->HandleCharacterFinishedSpawning(aCharacter);
  });

  UrsineEngine::ObjectPendingDeletion.Connect(*this, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectPendingDeletion(aObject);
  });
}

/******************************************************************************/
void BoardWaveManagerComponent::GenerateEncounter(UrsineEngine::GameObject& aBoard)
{
  // Determine the pool of enemies to choose from based on the current Act.
  std::vector<CharacterType>* characterPool = nullptr;
  switch(mAct)
  {
    case Act::eACT_ONE:
    {
      characterPool = &mActOneEncounters;
      break;
    }
    case Act::eACT_TWO:
    {
      characterPool = &mActTwoEncounters;
      break;
    }
    case Act::eACT_THREE:
    {
      characterPool = &mActThreeEncounters;
      break;
    }
    default:
    {
      break;
    }
  }

  if(characterPool != nullptr)
  {
    // Determine the number of enemies to spawn.
    int numEnemies = rand() % (mMaximumEnemies - mMinimumEnemies) + mMinimumEnemies;
    for(int i = 0; i < numEnemies; ++i)
    {
      auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
      if(boardLayoutComponent != nullptr)
      {
        // Try to place enemies as far to the right of the board as possible.
        //
        // Check each tile in each column, starting from the right. If that
        // tile doesn't have a character occupying it, add it to a list of
        // available tiles, then select one at random to place the new character.
        // If there are no available tiles, check the next column.
        auto columns = boardLayoutComponent->GetColumns();
        auto rows = boardLayoutComponent->GetRows();

        for(int c = columns - 1; c >= 0; --c)
        {
          std::vector<TileLocation> availableTiles;
          for(int r = 0; r < rows; ++r)
          {
            TileLocation location(c, r);
            auto character = boardLayoutComponent->GetCharacterAtLocation(location);
            if(character == nullptr)
            {
              availableTiles.emplace_back(location);
            }
          }

          if(!availableTiles.empty())
          {
            auto randomNumber = rand() % availableTiles.size();
            auto location = availableTiles.at(randomNumber);

            // Generate a name for the new enemy.
            int nameIndex = 0;
            std::stringstream nameStream;
            nameStream << "human";

            do
            {
              ++nameIndex;

              nameStream.str("");
              nameStream << "human_" << nameIndex;
            }
            while(aBoard.GetChild(nameStream.str()) != nullptr);

            // Randomly determine the type of enemy to create.
            randomNumber = rand() % characterPool->size();
            auto newEnemyType = characterPool->at(randomNumber);

            // Create the new enemy and add it to the board.
            auto newCharacter = CharacterFactory::CreateCharacter(newEnemyType, nameStream.str());
            boardLayoutComponent->AddCharacterAtLocation(std::move(newCharacter), location);
            mSpawningCharacters.emplace_back(boardLayoutComponent->GetCharacterAtLocation(location));

            // We have successfully placed a new enemy; break out of the loop
            // early and start placing the next enemy.
            break;
          }
        }
      }
    }
  }
}

/******************************************************************************/
void BoardWaveManagerComponent::HandleNewEnemyWaveRequested(UrsineEngine::GameObject& aBoard)
{
  auto parent = GetParent();
  if(parent != nullptr &&
     &aBoard == parent)
  {
    // Create a scrolling message the displays the wave number and keep
    // track of it. When the message is finished, GenerateEncounter()
    // will be called.
    std::stringstream displayStream;
    if(mWaveNumber < mWavesBeforeBoss)
    {
      ++mWaveNumber;
      displayStream << "Wave " << mWaveNumber;
    }
    else
    {
      displayStream << "Boss Approaching!";
    }

    auto waveDisplay = std::make_unique<UrsineEngine::GameObject>("waveDisplay");
    auto waveMessage = std::make_unique<ScrollingMessageBehaviorComponent>(displayStream.str(),
                                                                           BIGGEST_FONT_SIZE,
                                                                           200.0,
                                                                           15);
    waveDisplay->AddComponent(std::move(waveMessage));

    auto scene = env.GetCurrentScene();
    if(scene != nullptr)
    {
      if(scene->AddObject(std::move(waveDisplay)))
      {
        mWaveDisplay = scene->GetObjects().back();
      }
    }
  }
}

/******************************************************************************/
void BoardWaveManagerComponent::HandleCharacterFinishedSpawning(CharacterBehaviorComponent& aCharacter)
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

      if(mSpawningCharacters.empty())
      {
        auto parent = GetParent();
        if(parent != nullptr)
        {
          WaveFinishedSpawning.Notify(*parent);
        }
      }
    }
  }
}

/******************************************************************************/
void BoardWaveManagerComponent::HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject)
{
  if(mWaveDisplay != nullptr)
  {
    if(aObject == mWaveDisplay)
    {
      mWaveDisplay = nullptr;

      auto parent = GetParent();
      if(parent != nullptr)
      {
        GenerateEncounter(*parent);
      }
    }
  }
}
