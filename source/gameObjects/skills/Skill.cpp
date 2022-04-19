#include "Skill.hpp"

#include "Signals.hpp"

using Barebones::Skill;

/******************************************************************************/
Skill::Skill(UrsineEngine::GameObject& aParent)
  : mParent(&aParent)
{
}

/******************************************************************************/
void Skill::Execute(UrsineEngine::GameObject& aBoard,
                    const TileLocation& aLocation)
{
  ProtectedExecute(aBoard,
                   aLocation);
  SkillExecuted.Notify(*this);
}
