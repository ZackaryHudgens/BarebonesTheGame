#include "BoneThrowSkill.hpp"

using Barebones::BoneThrowSkill;

/******************************************************************************/
BoneThrowSkill::BoneThrowSkill(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
{
  SetName("Bone Throw");
  SetDescription("Throw 'em a bone.");
  SetDamage(2);
}
