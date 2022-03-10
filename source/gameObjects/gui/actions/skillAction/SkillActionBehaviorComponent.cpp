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
std::string SkillActionBehaviorComponent::GetSkillName() const
{
  std::string name;

  if(mSkill != nullptr)
  {
    name = mSkill->GetName();
  }

  return name;
}

/******************************************************************************/
std::string SkillActionBehaviorComponent::GetSkillDescription() const
{
  std::string description;

  if(mSkill != nullptr)
  {
    description = mSkill->GetDescription();
  }

  return description;
}

/******************************************************************************/
void SkillActionBehaviorComponent::HandleHoveredStatusChanged()
{
  // When hovered, update the glow color of the icon's shader.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto iconMesh = parent->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(iconMesh != nullptr)
    {
      auto shader = iconMesh->GetCurrentShader();
      if(shader != nullptr)
      {
        if(mHovered)
        {
          shader->Activate();
          shader->SetVec4("glowColor",
                          glm::vec4(1.0,
                                    0.0,
                                    1.0,
                                    1.0));
        }
        else
        {
          shader->Activate();
          shader->SetVec4("glowColor",
                          glm::vec4(1.0,
                                    1.0,
                                    1.0,
                                    1.0));
        }
      }
    }
  }
}

/******************************************************************************/
void SkillActionBehaviorComponent::HandleSelectionStatusChanged()
{
}
