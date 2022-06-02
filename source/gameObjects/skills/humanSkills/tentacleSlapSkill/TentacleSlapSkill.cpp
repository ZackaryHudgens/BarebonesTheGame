#include "TentacleSlapSkill.hpp"

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

#include "SlowEffect.hpp"

#include "Side.hpp"

using Barebones::TentacleSlapSkill;

/******************************************************************************/
TentacleSlapSkill::TentacleSlapSkill(UrsineEngine::GameObject& aCharacter)
  : SimpleSkill(aCharacter, 1)
{
  SetName("Tentacle Slap");
  SetDescription("Slaps with an outstretched tentacle. Slows the target.");
  SetDamage(2);
}

/******************************************************************************/
void TentacleSlapSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                         const TileLocation& aLocation)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto characterObject = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(characterObject != nullptr)
    {
      auto characterBehaviorComponent = characterObject->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        characterBehaviorComponent->AddEffect(std::make_unique<SlowEffect>());
      }
    }
  }
}
