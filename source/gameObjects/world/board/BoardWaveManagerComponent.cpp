#include "BoardWaveManagerComponent.hpp"

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
  , mBoard(nullptr)
  , mWaveDisplay(nullptr)
  , mWaveNumber(0)
{
  UrsineEngine::ObjectPendingDeletion.Connect(*this, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectPendingDeletion(aObject);
  });
}

/******************************************************************************/
void BoardWaveManagerComponent::GenerateEncounter(UrsineEngine::GameObject& aBoard)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    // Retrieve all the available spaces on the board, then select some at
    // random to add new enemies to.
    auto columns = boardLayoutComponent->GetColumns();
    auto rows = boardLayoutComponent->GetRows();

    std::vector<TileLocation> availableTiles;
    for(int c = 0; c < columns; ++c)
    {
      for(int r = 0; r < rows; ++r)
      {
        auto character = boardLayoutComponent->GetCharacterAtLocation(TileLocation(c, r));
        if(character == nullptr)
        {
          availableTiles.emplace_back(TileLocation(c, r));
        }
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

      // Add the new enemy to the board.
      auto newCharacter = CharacterFactory::CreateCharacter(CharacterType::eCORRUPTED_FARMER, nameStream.str());
      boardLayoutComponent->AddCharacterAtLocation(std::move(newCharacter), location);
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

      if(mBoard != nullptr)
      {
        GenerateEncounter(*mBoard);
      }
    }
  }
}
