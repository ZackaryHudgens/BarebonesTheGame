#include "BoardWaveManagerComponent.hpp"

#include <sstream>

#include "BoardLayoutComponent.hpp"

#include "CharacterFactory.hpp"

#include "Signals.hpp"
#include "TileUtil.hpp"

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
  , mWaveNumber(0)
{
  AllCharactersOfSideDefeated.Connect(*this, [this](UrsineEngine::GameObject& aBoard,
                                                    const Side& aSide)
  {
    this->HandleAllCharactersOfSideDefeated(aBoard, aSide);
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
void BoardWaveManagerComponent::HandleAllCharactersOfSideDefeated(UrsineEngine::GameObject& aBoard,
                                                                  const Side& aSide)
{
  if(&aBoard == GetParent())
  {
    switch(aSide)
    {
      case Side::eENEMY:
      {
        GenerateEncounter(aBoard);
        break;
      }
      default:
      {
        break;
      }
    }
  }
}
