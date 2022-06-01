#include "BoneThrowSkill.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::BoneThrowSkill;

/******************************************************************************/
BoneThrowSkill::BoneThrowSkill(UrsineEngine::GameObject& aParent)
  : SimpleSkill(aParent, 2)
{
  SetName("Bone Throw");
  SetDescription("Throw 'em a bone.");
  SetDamage(2);
}

/******************************************************************************/
void BoneThrowSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                      const TileLocation& aSourceLocation)
{
}
