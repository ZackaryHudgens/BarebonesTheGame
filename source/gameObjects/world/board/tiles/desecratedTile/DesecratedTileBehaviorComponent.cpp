#include "DesecratedTileBehaviorComponent.hpp"

#include "CharacterBehaviorComponent.hpp"

using Barebones::DesecratedTileBehaviorComponent;

/******************************************************************************/
DesecratedTileBehaviorComponent::DesecratedTileBehaviorComponent()
  : TileBehaviorComponent()
{
}

/******************************************************************************/
void DesecratedTileBehaviorComponent::HandleTurnEnded(UrsineEngine::GameObject& aCharacter)
{
  auto characterBehaviorComponent = aCharacter.GetFirstComponentOfType<CharacterBehaviorComponent>();
  if(characterBehaviorComponent != nullptr)
  {
    switch(characterBehaviorComponent->GetType())
    {
      case Type::eHUMAN:
      {
        characterBehaviorComponent->DealDamage(2);
        break;
      }
      case Type::eSKELETON:
      {
        characterBehaviorComponent->DealDamage(-2);
        break;
      }
      default:
      {
        break;
      }
    }
  }
}
