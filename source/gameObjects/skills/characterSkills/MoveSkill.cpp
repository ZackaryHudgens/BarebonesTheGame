#include "MoveSkill.hpp"

using Barebones::MoveSkill;

/******************************************************************************/
MoveSkill::MoveSkill()
  : Skill()
{
  SetName("Move");
  SetDescription("Moves the character.");
}

/******************************************************************************/
void MoveSkill::Execute(UrsineEngine::GameObject& aCharacter,
                        UrsineEngine::GameObject& aBoard,
                        const TileLocation& aLocation)
{
}

/******************************************************************************/
Barebones::TileList MoveSkill::GetValidTiles(UrsineEngine::GameObject& aCharacter,
                                             UrsineEngine::GameObject& aBoard,
                                             const TileLocation& aLocation)
{
  return TileList();
}
