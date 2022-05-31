#include "PitchforkSkill.hpp"

#include <Environment.hpp>
#include <Scene.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::PitchforkSkill;

/******************************************************************************/
PitchforkSkill::PitchforkSkill(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
{
  SetName("Pitchfork");
  SetDescription("Stabs with a pitchfork.");
  SetDamage(1);
}

/******************************************************************************/
void PitchforkSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                      const TileLocation& aLocation)
{
}

/******************************************************************************/
Barebones::TileList PitchforkSkill::GetValidTiles(UrsineEngine::GameObject& aBoard,
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
bool PitchforkSkill::IsEnemyAtLocation(UrsineEngine::GameObject& aBoard,
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
