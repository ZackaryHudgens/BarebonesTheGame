#include "ClawSkill.hpp"

#include "CharacterBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "ClawSkillEffectBehaviorComponent.hpp"

using Barebones::ClawSkill;

/******************************************************************************/
ClawSkill::ClawSkill(UrsineEngine::GameObject& aCharacter)
  : SimpleSkill(aCharacter, 1)
{
  SetName("Claw");
  SetDescription("Slashes with bony claws.");
  SetDamage(3);
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> ClawSkill::CreateVisualEffect(UrsineEngine::GameObject& aBoard,
                                                                        const TileLocation& aLocation)
{
  std::unique_ptr<UrsineEngine::GameObject> visualEffect = nullptr;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto targetCharacterObject = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(targetCharacterObject != nullptr)
    {
      // Create an effect in front of the target character.
      visualEffect = std::make_unique<UrsineEngine::GameObject>("clawEffect");
      visualEffect->AddComponent(std::make_unique<ClawSkillEffectBehaviorComponent>());
      visualEffect->SetPosition(targetCharacterObject->GetPosition());
    }
  }

  return std::move(visualEffect);
}
