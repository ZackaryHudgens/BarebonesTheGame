#include "Skill.hpp"

#include <algorithm>

#include "Signals.hpp"

using Barebones::Skill;

/******************************************************************************/
Skill::Skill(UrsineEngine::GameObject& aParent)
  : mParent(&aParent)
  , mEnabled(true)
{
}

/******************************************************************************/
void Skill::Execute(UrsineEngine::GameObject& aBoard,
                    const TileLocation& aLocation)
{
  if(mEnabled)
  {
    ProtectedExecute(aBoard,
                     aLocation);
    SkillExecuted.Notify(*this);
  }
}

/******************************************************************************/
bool Skill::IsTileValid(UrsineEngine::GameObject& aBoard,
                        const TileLocation& aLocation)
{
  bool success = false;

  auto tiles = GetValidTiles(aBoard);
  auto foundTile = std::find(tiles.begin(),
                             tiles.end(),
                             aLocation);
  if(foundTile != tiles.end())
  {
    success = true;
  }

  return success;
}
