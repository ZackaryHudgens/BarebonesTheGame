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
Barebones::TileList CharacterSkillComponent::GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                                                 const TileLocation& aLocation)
{
  return TileList();
}

/******************************************************************************/
Barebones::SkillSelectedSignal Barebones::SkillSelected;
Barebones::SkillExecutedSignal Barebones::SkillExecuted;
