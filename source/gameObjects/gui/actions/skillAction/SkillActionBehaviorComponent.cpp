#include "SkillActionBehaviorComponent.hpp"

#include <GameObject.hpp>
#include <MeshComponent.hpp>

#include "CharacterSkillComponent.hpp"

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
  // Scale up the parent object for use as an icon.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->SetScale(glm::vec3(200.0,
                               200.0,
                               1.0));
  }
}

/******************************************************************************/
void SkillActionBehaviorComponent::SetSkill(UrsineEngine::GameObject& aObject)
{
  mSkill = &aObject;
}

/******************************************************************************/
std::string SkillActionBehaviorComponent::GetSkillName() const
{
  std::string name;

  if(mSkill != nullptr)
  {
    auto skillComponent = mSkill->GetFirstComponentOfType<CharacterSkillComponent>();
    if(skillComponent != nullptr)
    {
      name = skillComponent->GetName();
    }
  }

  return name;
}

/******************************************************************************/
std::string SkillActionBehaviorComponent::GetSkillDescription() const
{
  std::string description;

  if(mSkill != nullptr)
  {
    auto skillComponent = mSkill->GetFirstComponentOfType<CharacterSkillComponent>();
    if(skillComponent != nullptr)
    {
      description = skillComponent->GetDescription();
    }
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
  if(mSkill != nullptr)
  {
    auto skillComponent = mSkill->GetFirstComponentOfType<CharacterSkillComponent>();
    if(skillComponent != nullptr)
    {
      skillComponent->Select();
    }
  }
}
