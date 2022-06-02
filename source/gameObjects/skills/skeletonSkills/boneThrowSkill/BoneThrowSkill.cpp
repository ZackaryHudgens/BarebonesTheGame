#include "BoneThrowSkill.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::BoneThrowSkill;

/******************************************************************************/
BoneThrowSkill::BoneThrowSkill(UrsineEngine::GameObject& aCharacter)
  : SimpleSkill(aCharacter, 2)
{
  SetName("Bone Throw");
  SetDescription("Throw 'em a bone.");
  SetDamage(2);
}
