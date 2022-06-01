#include "Skill.hpp"

#include <algorithm>

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::Skill;

/******************************************************************************/
Skill::Skill(UrsineEngine::GameObject& aParent)
  : mParent(&aParent)
  , mDamage(-1)
  , mEnabled(true)
{
}

/******************************************************************************/
void Skill::Select(UrsineEngine::GameObject& aBoard)
{
  ProtectedSelect(aBoard);
  SkillSelected.Notify(*this);
}

/******************************************************************************/
void Skill::Execute(UrsineEngine::GameObject& aBoard,
                    const TileLocation& aLocation)
{
  if(mEnabled)
  {
    auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      for(const auto& affectedTile : GetAffectedTiles(aBoard, aLocation))
      {
        auto character = boardLayoutComponent->GetCharacterAtLocation(affectedTile);
        if(character != nullptr)
        {
          auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
          if(characterBehaviorComponent != nullptr &&
             mDamage >= 0)
          {
            characterBehaviorComponent->DealDamage(mDamage);
          }
        }

        ProtectedExecute(aBoard, affectedTile);
      }
    }

    SkillExecuted.Notify(*this);
  }
}

/******************************************************************************/
void Skill::Cancel()
{
  ProtectedCancel();
  SkillCancelled.Notify(*this);
}

/******************************************************************************/
void Skill::SetEnabled(bool aEnabled)
{
  mEnabled = aEnabled;
  HandleEnabledChanged(mEnabled);
}

/******************************************************************************/
bool Skill::IsTileValid(UrsineEngine::GameObject& aBoard,
                        const TileLocation& aSourceLocation,
                        const TileLocation& aTargetLocation)
{
  bool success = false;

  auto tiles = GetValidTiles(aBoard, aSourceLocation);
  auto foundTile = std::find(tiles.begin(),
                             tiles.end(),
                             aTargetLocation);
  if(foundTile != tiles.end())
  {
    success = true;
  }

  return success;
}

/******************************************************************************/
Barebones::TileList Skill::GetAffectedTiles(UrsineEngine::GameObject& aBoard,
                                            const TileLocation& aSourceLocation)
{
  TileList tiles;
  tiles.emplace_back(aSourceLocation);
  return tiles;
}

/******************************************************************************/
bool Skill::IsEnemyAtLocation(UrsineEngine::GameObject& aBoard,
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
