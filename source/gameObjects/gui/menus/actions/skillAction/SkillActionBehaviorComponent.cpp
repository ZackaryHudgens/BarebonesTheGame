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
void SkillActionBehaviorComponent::Select()
{
  if(mSkill != nullptr)
  {
    if(mSkill->IsEnabled())
    {
      SkillSelectedFromMenu.Notify(*mSkill);
    }
  }
}

/******************************************************************************/
void SkillActionBehaviorComponent::SetSkill(Skill& aSkill)
{
  mSkill = &aSkill;
}
