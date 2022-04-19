#include "ClawSkill.hpp"

#include <Environment.hpp>
#include <Scene.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "SkillEffectFactory.hpp"

using Barebones::ClawSkill;

/******************************************************************************/
ClawSkill::ClawSkill(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
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
        auto parentObject = GetParent();
        if(parentObject != nullptr)
        {
          auto characterBehaviorComponent = parentObject->GetFirstComponentOfType<CharacterBehaviorComponent>();
          if(characterBehaviorComponent != nullptr)
          {
            auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(parentObject->GetName());
            auto targetCharacterLocation = boardLayoutComponent->GetLocationOfCharacter(targetCharacterObject->GetName());

            // Move the character in different directions based on the target location.
            auto characterPos = parentObject->GetPosition();
            auto xDifference = characterLocation.first - targetCharacterLocation.first;
            auto yDifference = characterLocation.second - targetCharacterLocation.second;
            if(xDifference > 0)
            {
              // This character is to the right of the target.
              characterPos.x -= 0.2;
            }
            else if(xDifference < 0)
            {
              // This character is to the left of the target.
              characterPos.x += 0.2;
            }
            else if(xDifference == 0)
            {
              if(yDifference > 0)
              {
                // This character is above the target.
                characterPos.z += 0.2;
              }
              else if(yDifference < 0)
              {
                // This character is below the target.
                characterPos.z -= 0.2;
              }
            }

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

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto characterBehaviorComponent = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(characterBehaviorComponent != nullptr)
    {
      auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
      if(boardLayoutComponent != nullptr)
      {
        auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());

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
