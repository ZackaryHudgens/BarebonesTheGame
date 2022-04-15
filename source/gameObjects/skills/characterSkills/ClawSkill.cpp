#include "ClawSkill.hpp"

#include <Environment.hpp>
#include <Scene.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "SkillEffectFactory.hpp"

using Barebones::ClawSkill;

/******************************************************************************/
ClawSkill::ClawSkill(UrsineEngine::GameObject& aCharacter)
  : Skill(aCharacter)
  , mDamage(3)
{
  SetName("Claw");
  SetDescription("Slashes with bony claws.");
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
      auto targetCharacterBehaviorComponent = targetCharacterObject->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(targetCharacterBehaviorComponent != nullptr)
      {
        auto scene = env.GetCurrentScene();
        if(scene != nullptr)
        {
          // Create an effect in front of the target character.
          auto effectObject = SkillEffectFactory::CreateEffect(SkillType::eCLAW, "clawEffect");
          auto targetPosition = targetCharacterObject->GetPosition();
          targetPosition.z += 0.1;
          effectObject->SetPosition(targetPosition);

          scene->AddObject(std::move(effectObject));
        }

        // Move the character to indicate attacking.
        auto characterObject = GetCharacter();
        if(characterObject != nullptr)
        {
          auto characterBehaviorComponent = characterObject->GetFirstComponentOfType<CharacterBehaviorComponent>();
          if(characterBehaviorComponent != nullptr)
          {
            auto characterPos = characterObject->GetPosition();
            characterPos.x += 0.2;
            characterBehaviorComponent->MoveToPosition(characterPos,
                                                       0.3,
                                                       true);
          }
        }

        targetCharacterBehaviorComponent->DealDamage(mDamage);
      }
    }
  }
}

/******************************************************************************/
Barebones::TileList ClawSkill::GetValidTiles(UrsineEngine::GameObject& aBoard)
{
  TileList tiles;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(GetCharacter()->GetName());

    // Check to the right.
    auto targetLocation = characterLocation;
    targetLocation.first = characterLocation.first + 1;
    if(IsEnemyAtLocation(aBoard,
                         targetLocation))
    {
      tiles.emplace_back(targetLocation);
    }

    // Check to the left.
    targetLocation.first = characterLocation.first - 1;
    if(IsEnemyAtLocation(aBoard,
                         targetLocation))
    {
      tiles.emplace_back(targetLocation);
    }

    targetLocation.first = characterLocation.first;

    // Check above.
    targetLocation.second = characterLocation.second + 1;
    if(IsEnemyAtLocation(aBoard,
                         targetLocation))
    {
      tiles.emplace_back(targetLocation);
    }

    // Check below.
    targetLocation.second = characterLocation.second - 1;
    if(IsEnemyAtLocation(aBoard,
                         targetLocation))
    {
      tiles.emplace_back(targetLocation);
    }
  }

  return tiles;
}

/******************************************************************************/
bool ClawSkill::IsEnemyAtLocation(UrsineEngine::GameObject& aBoard,
                                   const TileLocation& aLocation)
{
  bool success = false;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto target = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(target != nullptr)
    {
      auto characterBehaviorComponent = target->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        if(characterBehaviorComponent->GetSide() == Side::eENEMY)
        {
          success = true;
        }
      }
    }
  }

  return success;
}
