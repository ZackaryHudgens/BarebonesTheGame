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
  SkillSelected.Notify(*this);
}

/******************************************************************************/
void CharacterSkillComponent::Execute()
{
  ProtectedExecute();
  SkillExecuted.Notify(*this);
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::MeshComponent> CharacterSkillComponent::GetIcon()
{
  return std::make_unique<UrsineEngine::MeshComponent>();
}

/******************************************************************************/
Barebones::SkillSelectedSignal Barebones::SkillSelected;
Barebones::SkillExecutedSignal Barebones::SkillExecuted;
