#include "MoveSkill.hpp"

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

using Barebones::MoveSkill;

/******************************************************************************/
MoveSkill::MoveSkill(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
{
  SetName("Move");
  SetDescription("Moves the character.");
}

/******************************************************************************/
void MoveSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                 const TileLocation& aLocation)
{
  auto parent = GetParent();
  auto characterBehaviorComponent = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(characterBehaviorComponent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());
    boardLayoutComponent->MoveCharacter(characterLocation,
                                        aLocation);
  }
}

/******************************************************************************/
Barebones::TileList MoveSkill::GetValidTiles(UrsineEngine::GameObject& aBoard)
{
  TileList tiles;

  auto parent = GetParent();
  auto characterBehaviorComponent = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(characterBehaviorComponent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());
    auto shortestPaths = characterBehaviorComponent->GenerateShortestPathList(aBoard, characterLocation);

    for(const auto& shortestPath : shortestPaths)
    {
      if(shortestPath.second < characterBehaviorComponent->GetSpeed())
      {
        for(const auto& tile : shortestPath.first)
        {
          tiles.emplace_back(tile);
        }
      }
    }
  }

  return tiles;
}
