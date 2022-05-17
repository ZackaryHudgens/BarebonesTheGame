#include "SkillActionBehaviorComponent.hpp"

using Barebones::SkillActionBehaviorComponent;

/******************************************************************************/
SkillActionBehaviorComponent::SkillActionBehaviorComponent()
  : ActionBehaviorComponent()
  , mSkill(nullptr)
{
}

/******************************************************************************/
void SkillActionBehaviorComponent::SetSkill(Skill& aSkill)
{
  mSkill = &aSkill;
}

/******************************************************************************/
void SkillActionBehaviorComponent::ProtectedExecute()
{
  if(mSkill != nullptr)
  {
    mSkill->Select();
  }
}
