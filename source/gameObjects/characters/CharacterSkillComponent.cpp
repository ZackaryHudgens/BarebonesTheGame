#include "CharacterSkillComponent.hpp"

using Barebones::CharacterSkillComponent;

/******************************************************************************/
CharacterSkillComponent::CharacterSkillComponent()
  : mHighlightColor(1.0, 1.0, 1.0)
{
}

/******************************************************************************/
void CharacterSkillComponent::Select()
{
  ProtectedSelect();
  SkillSelected.Notify(*this);
}

/******************************************************************************/
void CharacterSkillComponent::Execute(UrsineEngine::GameObject& aBoard,
                                      const TileLocation& aLocation)
{
  ProtectedExecute(aBoard,
                   aLocation);
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
