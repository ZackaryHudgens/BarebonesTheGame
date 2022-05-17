#include "SkillActionBehaviorComponent.hpp"

#include <GameObject.hpp>
#include <MeshComponent.hpp>

#include "Signals.hpp"

using Barebones::SkillActionBehaviorComponent;

/******************************************************************************/
SkillActionBehaviorComponent::SkillActionBehaviorComponent()
  : ActionBehaviorComponent()
  , mSkill(nullptr)
{
}

/******************************************************************************/
void SkillActionBehaviorComponent::Initialize()
{
}

/******************************************************************************/
void SkillActionBehaviorComponent::SetHovered(bool aHovered)
{
}

/******************************************************************************/
void SkillActionBehaviorComponent::SetSkill(Skill& aSkill)
{
  mSkill = &aSkill;
}

/******************************************************************************/
void SkillActionBehaviorComponent::ProtectedSelect()
{
  if(mSkill != nullptr)
  {
    mSkill->Select();
    SkillSelectedFromMenu.Notify(*mSkill);
  }
}
