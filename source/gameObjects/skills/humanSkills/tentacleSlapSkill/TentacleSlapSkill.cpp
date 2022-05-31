#include "TentacleSlapSkill.hpp"

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

#include "SlowEffect.hpp"

#include "Side.hpp"

using Barebones::TentacleSlapSkill;

/******************************************************************************/
TentacleSlapSkill::TentacleSlapSkill(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
{
  SetName("Tentacle Slap");
  SetDescription("Slaps with an outstretched tentacle. Slows the target.");
  SetDamage(2);
}

/******************************************************************************/
Barebones::TileList TentacleSlapSkill::GetValidTiles(UrsineEngine::GameObject& aBoard,
                                                     const TileLocation& aSourceLocation)
{
  TileList tiles;

  // Check to the right.
  auto targetLocation = aSourceLocation;
  targetLocation.first += 1;
  if(IsEnemyAtLocation(aBoard,
                       targetLocation))
  {
    tiles.emplace_back(targetLocation);
  }

  // Check to the left.
  targetLocation = aSourceLocation;
  targetLocation.first -= 1;
  if(IsEnemyAtLocation(aBoard,
                       targetLocation))
  {
    tiles.emplace_back(targetLocation);
  }

  // Check above.
  targetLocation = aSourceLocation;
  targetLocation.second += 1;
  if(IsEnemyAtLocation(aBoard,
                       targetLocation))
  {
    tiles.emplace_back(targetLocation);
  }

  // Check below.
  targetLocation = aSourceLocation;
  targetLocation.second -= 1;
  if(IsEnemyAtLocation(aBoard,
                       targetLocation))
  {
    tiles.emplace_back(targetLocation);
  }

  return tiles;
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
bool TentacleSlapSkill::IsEnemyAtLocation(UrsineEngine::GameObject& aBoard,
                                          const TileLocation& aLocation)
{
  bool success = false;

  // Get the side of the parent character.
  Side characterSide = Side::eNONE;
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto characterBehaviorComponent = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(characterBehaviorComponent != nullptr)
    {
      characterSide = characterBehaviorComponent->GetSide();
    }
  }

  // Any character not on the parent character's side is considered an enemy.
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto target = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(target != nullptr)
    {
      auto characterBehaviorComponent = target->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        if(characterBehaviorComponent->GetSide() != characterSide)
        {
          success = true;
        }
      }
    }
  }

  return success;
}
