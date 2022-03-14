#include "SkillActionBehaviorComponent.hpp"

#include <GameObject.hpp>
#include <MeshComponent.hpp>

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
void SkillActionBehaviorComponent::SetSkill(Skill& aSkill)
{
  mSkill = &aSkill;
}

/******************************************************************************/
void SkillActionBehaviorComponent::HandleHoveredStatusChanged()
{
}

/******************************************************************************/
void SkillActionBehaviorComponent::HandleSelectionStatusChanged()
{
}
