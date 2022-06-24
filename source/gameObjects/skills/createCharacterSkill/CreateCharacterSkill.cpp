#include "CreateCharacterSkill.hpp"

#include <sstream>

#include "BoardLayoutComponent.hpp"

using Barebones::CreateCharacterSkill;

/******************************************************************************/
CreateCharacterSkill::CreateCharacterSkill()
  : Skill()
  , mTypeToCreate(CharacterType::eNONE)
{
}

/******************************************************************************/
Barebones::TileList CreateCharacterSkill::GetValidTiles(UrsineEngine::GameObject& aBoard,
                                                        const TileLocation& aSourceLocation)
{
  TileList tiles;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    int columns = boardLayoutComponent->GetColumns();
    int rows = boardLayoutComponent->GetRows();

    for(int c = 0; c < columns; ++c)
    {
      for(int r = 0; r < rows; ++r)
      {
        TileLocation location(c, r);
        auto character = boardLayoutComponent->GetCharacterAtLocation(location);
        if(character == nullptr)
        {
          tiles.emplace_back(location);
        }
      }
    }
  }

  return tiles;
}

/******************************************************************************/
void CreateCharacterSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                            const TileLocation& aLocation)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    std::stringstream nameStream;
    int index = 0;
    do
    {
      nameStream.str("");
      nameStream << "newCharacter_" << aLocation.first << "_" << aLocation.second;
      nameStream << "_" << index;
      ++index;
    }while(aBoard.GetChild(nameStream.str()) != nullptr);

    auto character = CharacterFactory::CreateCharacter(mTypeToCreate, nameStream.str());
    boardLayoutComponent->AddCharacterAtLocation(std::move(character), aLocation);
  }
}
