#include "ClawSkill.hpp"

#include <Environment.hpp>
#include <Scene.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "ClawSkillEffectBehaviorComponent.hpp"

using Barebones::ClawSkill;

/******************************************************************************/
ClawSkill::ClawSkill(UrsineEngine::GameObject& aParent)
  : SimpleSkill(aParent, 1)
{
  SetName("Claw");
  SetDescription("Slashes with bony claws.");
  SetDamage(3);
}

/******************************************************************************/
void ClawSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                 const TileLocation& aLocation)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto targetCharacterObject = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(targetCharacterObject != nullptr)
    {
      auto scene = env.GetCurrentScene();
      if(scene != nullptr)
      {
        // Create an effect in front of the target character.
        auto effectObject = std::make_unique<UrsineEngine::GameObject>("clawEffect");
        effectObject->AddComponent(std::make_unique<ClawSkillEffectBehaviorComponent>());
        effectObject->SetPosition(targetCharacterObject->GetPosition());

        scene->AddObject(std::move(effectObject));
      }
    }
  }
}
