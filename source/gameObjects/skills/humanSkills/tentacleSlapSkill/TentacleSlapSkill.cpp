#include "TentacleSlapSkill.hpp"

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

#include "SlowEffect.hpp"

#include "ColorChangeVisualEffectBehaviorComponent.hpp"

#include "Colors.hpp"
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

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> TentacleSlapSkill::CreateVisualEffect(UrsineEngine::GameObject& aBoard,
                                                                                const TileLocation& aLocation)
{
  std::unique_ptr<UrsineEngine::GameObject> visualEffect = nullptr;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto character = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(character != nullptr)
    {
      visualEffect = std::make_unique<UrsineEngine::GameObject>("tentacleSlapVisualEffect");
      visualEffect->AddComponent(std::make_unique<ColorChangeVisualEffectBehaviorComponent>(*character,
                                                                                            LIGHT_COLOR,
                                                                                            0.1));
    }
  }

  return std::move(visualEffect);
}
