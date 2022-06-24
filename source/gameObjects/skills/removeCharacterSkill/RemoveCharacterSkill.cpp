#include "RemoveCharacterSkill.hpp"

#include "BoardLayoutComponent.hpp"

#include "Signals.hpp"

using Barebones::RemoveCharacterSkill;

/******************************************************************************/
RemoveCharacterSkill::RemoveCharacterSkill()
  : Skill()
  , mTypeToRemove(Type::eNONE)
{
}

/******************************************************************************/
Barebones::TileList RemoveCharacterSkill::GetValidTiles(UrsineEngine::GameObject& aBoard,
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
        if(character != nullptr)
        {
          auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
          if(characterBehaviorComponent != nullptr)
          {
            if(characterBehaviorComponent->GetType() == mTypeToRemove)
            {
              tiles.emplace_back(location);
            }
          }
        }
      }
    }
  }

  return tiles;
}

/******************************************************************************/
void RemoveCharacterSkill::ProtectedSelect(UrsineEngine::GameObject& aBoard)
{
  DisplayHintRequested.Notify("Choose a skeleton to remove.");
}

/******************************************************************************/
void RemoveCharacterSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                            const TileLocation& aLocation)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto character = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(character != nullptr)
    {
      auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        characterBehaviorComponent->SetCurrentHealth(0);
      }
    }
  }

  DisplayHintRequested.Notify("");
}

/******************************************************************************/
void RemoveCharacterSkill::ProtectedCancel()
{
  DisplayHintRequested.Notify("");
}
