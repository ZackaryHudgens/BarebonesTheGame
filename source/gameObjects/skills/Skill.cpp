#include "Skill.hpp"

#include <algorithm>

#include <CoreSignals.hpp>
#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::Skill;

/******************************************************************************/
Skill::Skill(UrsineEngine::GameObject& aCharacter)
  : mCharacter(&aCharacter)
  , mVisualEffect(nullptr)
  , mBoard(nullptr)
  , mExecuteLocation(-1, -1)
  , mDamage(-1)
  , mEnabled(true)
{
  UrsineEngine::ObjectPendingDeletion.Connect(mObserver, [this](UrsineEngine::GameObject* aObject)
  {
    this->HandleObjectPendingDeletion(aObject);
  });
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
    mBoard = &aBoard;
    mExecuteLocation = aLocation;

    auto visualEffect = CreateVisualEffect(aBoard, aLocation);
    if(visualEffect != nullptr)
    {
      // Add the visual effect to the scene.
      auto scene = env.GetCurrentScene();
      if(scene != nullptr)
      {
        scene->AddObject(std::move(visualEffect));
        mVisualEffect = scene->GetObjects().back();
      }
    }
    else
    {
      PrivateExecute(aBoard, mExecuteLocation);
    }
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
Barebones::TileList Skill::GetValidTiles(UrsineEngine::GameObject& aBoard)
{
  return GetValidTiles(aBoard, GetCharacterLocation(aBoard));
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
bool Skill::IsTileValid(UrsineEngine::GameObject& aBoard,
                        const TileLocation& aTargetLocation)
{
  return IsTileValid(aBoard, GetCharacterLocation(aBoard), aTargetLocation);
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
Barebones::TileLocation Skill::GetCharacterLocation(UrsineEngine::GameObject& aBoard)
{
  TileLocation characterLocation(-1, -1);

  auto character = GetCharacter();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(character != nullptr &&
     boardLayoutComponent != nullptr)
  {
    characterLocation = boardLayoutComponent->GetLocationOfCharacter(character->GetName());
  }

  return characterLocation;
}

/******************************************************************************/
bool Skill::IsEnemyAtLocation(UrsineEngine::GameObject& aBoard,
                              const TileLocation& aLocation)
{
  bool success = false;

  // Get the side of the parent character.
  Side characterSide = Side::eNONE;
  auto character = GetCharacter();
  if(character != nullptr)
  {
    auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
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

/******************************************************************************/
void Skill::PrivateExecute(UrsineEngine::GameObject& aBoard,
                           const TileLocation& aLocation)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    for(const auto& affectedTile : GetAffectedTiles(*mBoard, mExecuteLocation))
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

      ProtectedExecute(*mBoard, affectedTile);
    }
  }

  SkillExecuted.Notify(*this);
}

/******************************************************************************/
void Skill::HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject)
{
  if(aObject == mVisualEffect &&
     mBoard != nullptr)
  {
    PrivateExecute(*mBoard, mExecuteLocation);

    mVisualEffect = nullptr;
    mBoard = nullptr;
  }
}
