#include "DamageAction.hpp"

#include <sstream>

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

using Barebones::DamageAction;

/******************************************************************************/
DamageAction::DamageAction()
  : SkillAction()
  , mDamage(0)
{
  std::stringstream description;
  description << "Deals " << mDamage << " damage.";
  SetDescription(description.str());
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

/******************************************************************************/
void DamageAction::SetDamage(int aDamage)
{
  mDamage = aDamage;

  std::stringstream description;
  description << "Deals " << mDamage << " damage.";
  SetDescription(description.str());
}
