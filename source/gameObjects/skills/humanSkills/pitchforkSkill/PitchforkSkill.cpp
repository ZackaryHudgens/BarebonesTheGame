#include "PitchforkSkill.hpp"

using Barebones::PitchforkSkill;

/******************************************************************************/
PitchforkSkill::PitchforkSkill(UrsineEngine::GameObject& aCharacter)
  : SingleTargetSkill(aCharacter, 1)
{
  SetName("Pitchfork");
  SetDescription("Stabs with a pitchfork.");
  SetDamage(1);
}
