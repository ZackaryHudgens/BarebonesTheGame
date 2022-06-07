#include "DamageAction.hpp"

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

using Barebones::DamageAction;

/******************************************************************************/
DamageAction::DamageAction()
  : SkillAction()
  , mDamage(0)
{
}

/******************************************************************************/
void DamageAction::Execute(UrsineEngine::GameObject& aBoard,
                           const TileLocation& aLocation)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto character = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(character != nullptr)
    {
      auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        characterBehaviorComponent->DealDamage(mDamage);
      }
    }
  }
}
