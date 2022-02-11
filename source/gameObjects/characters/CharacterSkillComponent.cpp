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

  auto parent = GetParent();
  if(parent != nullptr)
  {
    SkillSelected.Notify(*parent);
  }
}

/******************************************************************************/
void CharacterSkillComponent::Execute(UrsineEngine::GameObject& aBoard,
                                      const TileLocation& aLocation)
{
  ProtectedExecute(aBoard,
                   aLocation);

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
Barebones::TileList CharacterSkillComponent::GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                                                 const TileLocation& aLocation)
{
  return TileList();
}

/******************************************************************************/
Barebones::SkillSelectedSignal Barebones::SkillSelected;
Barebones::SkillExecutedSignal Barebones::SkillExecuted;
