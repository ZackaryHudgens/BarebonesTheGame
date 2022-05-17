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
void Skill::Select()
{
  ProtectedSelect();
  SkillSelected.Notify(*this);
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
void Skill::Cancel()
{
  ProtectedCancel();
  SkillCancelled.Notify(*this);
}

/******************************************************************************/
void Skill::SetEnabled(bool aEnabled)
{
  mEnabled = aEnabled;
  HandleEnabledChanged(mEnabled);
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
