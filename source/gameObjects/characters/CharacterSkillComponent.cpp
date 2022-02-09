#include "CharacterSkillComponent.hpp"

using Barebones::CharacterSkillComponent;

/******************************************************************************/
CharacterSkillComponent::CharacterSkillComponent()
{
}

/******************************************************************************/
void CharacterSkillComponent::Select()
{
  ProtectedSelect();

  auto parent = GetParent();
  if(parent != nullptr)
  {
    SkillSelected.Notify(*parent);
  }
}

/******************************************************************************/
void CharacterSkillComponent::Execute()
{
  ProtectedExecute();

  auto parent = GetParent();
  if(parent != nullptr)
  {
    SkillExecuted.Notify(*parent);
  }
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::MeshComponent> CharacterSkillComponent::GetIcon()
{
  return std::make_unique<UrsineEngine::MeshComponent>();
}

/******************************************************************************/
Barebones::SkillSelectedSignal Barebones::SkillSelected;
Barebones::SkillExecutedSignal Barebones::SkillExecuted;
