#include "Skill.hpp"

#include "Signals.hpp"

using Barebones::Skill;

/******************************************************************************/
Skill::Skill(UrsineEngine::GameObject& aCharacter)
  : mCharacter(&aCharacter)
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
