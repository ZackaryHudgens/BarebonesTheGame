#include "PitchforkSkill.hpp"

#include <Environment.hpp>
#include <Scene.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::PitchforkSkill;

/******************************************************************************/
PitchforkSkill::PitchforkSkill(UrsineEngine::GameObject& aParent)
  : SimpleSkill(aParent, 1)
{
  SetName("Pitchfork");
  SetDescription("Stabs with a pitchfork.");
  SetDamage(1);
}

/******************************************************************************/
void PitchforkSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                      const TileLocation& aLocation)
{
}
