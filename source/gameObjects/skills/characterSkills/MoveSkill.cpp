#include "MoveSkill.hpp"

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

using Barebones::MoveSkill;

/******************************************************************************/
MoveSkill::MoveSkill(UrsineEngine::GameObject& aCharacter)
  : Skill(aCharacter)
{
  SetName("Move");
  SetDescription("Moves the character.");
}

/******************************************************************************/
void MoveSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                 const TileLocation& aLocation)
{
  auto character = GetCharacter();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(character->GetName());
    boardLayoutComponent->MoveCharacter(characterLocation,
                                        aLocation);
  }
}

/******************************************************************************/
Barebones::TileList MoveSkill::GetValidTiles(UrsineEngine::GameObject& aBoard)
{
  TileList tiles;

  auto character = GetCharacter();
  auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(characterBehaviorComponent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(character->GetName());
    tiles = characterBehaviorComponent->GetMovements(aBoard,
                                                     characterLocation);
  }

  return tiles;
}
