#include "Skill.hpp"

#include <algorithm>
#include <sstream>

#include <CoreSignals.hpp>
#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::Skill;

/******************************************************************************/
Skill::Skill()
  : mCharacter(nullptr)
  , mBoard(nullptr)
  , mExecuteLocation(-1, -1)
  , mEnabled(true)
{
  SkillVisualEffectFinished.Connect(mObserver, [this](UrsineEngine::GameObject& aVisualEffect)
  {
    this->HandleSkillVisualEffectFinished(aVisualEffect);
  });
}

/******************************************************************************/
std::string Skill::GetDescription() const
{
  std::stringstream description;
  description << mFluffDescription;

  for(const auto& action : mActions)
  {
    description << " ";
    description << action->GetDescription();
  }

  return description.str();
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

    // Create visual effects and add them to the current scene.
    auto scene = env.GetCurrentScene();
    if(scene != nullptr)
    {
      std::stringstream nameStream;
      for(const auto& visualEffectType : mVisualEffects)
      {
        // Create a visual effect for each affected tile.
        for(const auto& affectedTile : GetAffectedTiles(aBoard, aLocation))
        {
          int nameIndex = 0;
          do
          {
            // Generate a name for this visual effect.
            nameStream.str("");
            if(mCharacter != nullptr)
            {
              nameStream << mCharacter->GetName() << "_";
            }
            nameStream << "visualEffect_" << affectedTile.first << "_" << affectedTile.second << "_";

            ++nameIndex;
            nameStream << nameIndex;
          }
          while(scene->GetObject(nameStream.str()) != nullptr);

          // Create the visual effect and add it to the scene.
          auto visualEffectObject = VisualEffectFactory::CreateVisualEffect(nameStream.str(),
                                                                            visualEffectType,
                                                                            aBoard,
                                                                            GetCharacterLocation(aBoard),
                                                                            affectedTile);
          scene->AddObject(std::move(visualEffectObject));
          mActiveVisualEffects.emplace_back(scene->GetObjects().back());
        }
      }
    }

    // If there are no active visual effects, execute the skill immediately.
    if(mActiveVisualEffects.empty())
    {
      PrivateExecute(aBoard, aLocation);
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
void Skill::AddAction(std::unique_ptr<SkillAction> aAction)
{
  mActions.emplace_back(std::move(aAction));
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
  // Execute each action on each affected tile, then call ProtectedExecute()
  // for any custom logic.
  auto affectedTiles = GetAffectedTiles(aBoard, aLocation);
  for(const auto& tile : affectedTiles)
  {
    for(auto& action : mActions)
    {
      action->Execute(aBoard, tile);
    }
  }

  ProtectedExecute(aBoard, aLocation);

  SkillExecuted.Notify(*this);
}

/******************************************************************************/
void Skill::HandleSkillVisualEffectFinished(UrsineEngine::GameObject& aVisualEffect)
{
  auto name = aVisualEffect.GetName();
  auto findObject = [&name](UrsineEngine::GameObject* aObject)
  {
    return aObject->GetName() == name;
  };

  auto foundObject = std::find_if(mActiveVisualEffects.begin(),
                                  mActiveVisualEffects.end(),
                                  findObject);
  if(foundObject != mActiveVisualEffects.end())
  {
    mActiveVisualEffects.erase(foundObject);

    // If no visual effects remain, execute this skill.
    if(mActiveVisualEffects.empty())
    {
      if(mBoard != nullptr)
      {
        PrivateExecute(*mBoard, mExecuteLocation);
        mBoard = nullptr;
        mExecuteLocation = TileLocation(-1, -1);
      }
    }
  }
}
