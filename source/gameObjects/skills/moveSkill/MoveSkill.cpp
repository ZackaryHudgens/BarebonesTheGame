#include "MoveSkill.hpp"

#include <algorithm>
#include <sstream>

#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

using Barebones::MoveSkill;

/******************************************************************************/
MoveSkill::MoveSkill()
  : Skill()
  , mSkillEffect(nullptr)
  , mDistanceRemaining(0)
{
  SetName("Move");
  SetFluffDescription("Moves the character.");
}

/******************************************************************************/
Barebones::TileList MoveSkill::GetValidTiles(UrsineEngine::GameObject& aBoard,
                                             const TileLocation& aSourceLocation)
{
  TileList tiles;

  // If the shortest path list hasn't been generated in ProtectedSelect(),
  // generate it here.
  if(mShortestPaths.empty())
  {
    auto character = GetCharacter();
    auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
    auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
    if(characterBehaviorComponent != nullptr &&
       boardLayoutComponent != nullptr)
    {
      mShortestPaths = characterBehaviorComponent->GenerateShortestPathList(aBoard, aSourceLocation);
    }
  }

  for(const auto& shortestPath : mShortestPaths)
  {
    if(shortestPath.second <= mDistanceRemaining)
    {
      for(const auto& tile : shortestPath.first)
      {
        tiles.emplace_back(tile);
      }
    }
  }

  return tiles;
}

/******************************************************************************/
void MoveSkill::ProtectedSelect(UrsineEngine::GameObject& aBoard)
{
  // Generate a list of shortest paths on this board for the parent character.
  auto character = GetCharacter();
  if(character != nullptr)
  {
    auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
    auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(boardLayoutComponent != nullptr &&
       characterBehaviorComponent != nullptr)
    {
      auto characterLocation = GetCharacterLocation(aBoard);
      mShortestPaths = characterBehaviorComponent->GenerateShortestPathList(aBoard, characterLocation);

      // Create a MoveSkillEffectBehaviorComponent and add it to a GameObject,
      // then add the GameObject to the scene. This component will highlight
      // tiles as the user moves around, to show a preview of each shortest
      // path before the user executes this skill.
      auto scene = env.GetCurrentScene();
      if(scene != nullptr)
      {
        auto skillEffectObject = std::make_unique<UrsineEngine::GameObject>("moveSkillEffect");
        skillEffectObject->AddComponent(std::make_unique<MoveSkillEffectBehaviorComponent>(*this));
        scene->AddObject(std::move(skillEffectObject));

        mSkillEffect = scene->GetObjects().back()->GetFirstComponentOfType<MoveSkillEffectBehaviorComponent>();
        mSkillEffect->SetBoard(aBoard);
        mSkillEffect->SetShortestPathList(mShortestPaths);
        mSkillEffect->SetStartingLocation(characterLocation);
      }
    }
  }
}

/******************************************************************************/
void MoveSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                 const TileLocation& aLocation)
{
  auto character = GetCharacter();
  auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(characterBehaviorComponent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto characterLocation = GetCharacterLocation(aBoard);

    // If the shortest path list hasn't been generated in ProtectedSelect(),
    // generate it here.
    if(mShortestPaths.empty())
    {
      mShortestPaths = characterBehaviorComponent->GenerateShortestPathList(aBoard, characterLocation);
    }

    // Returns true if aLocation is the last TileLocation in the TileList.
    auto isPath = [&aLocation](const TilePath& aPath)
    {
      bool success = false;

      if(!aPath.first.empty())
      {
        success = aPath.first.back() == aLocation;
      }

      return success;
    };

    // Find the path in mShortestPaths that ends in aLocation.
    auto path = std::find_if(mShortestPaths.begin(),
                             mShortestPaths.end(),
                             isPath);
    if(path != mShortestPaths.end())
    {
      boardLayoutComponent->MoveCharacterAlongPath(characterLocation,
                                                   path->first);

      // After moving the character, the board state has changed,
      // so the shortest paths are no longer valid.
      mShortestPaths.clear();

      // Subtract the shortest distance from the distance remaining. If no distance
      // remains, disable this skill.
      mDistanceRemaining -= path->second;
      if(mDistanceRemaining <= 0)
      {
        SetEnabled(false);
      }

      // Update the description.
      std::stringstream description;
      description << "Moves the character.";
      description << " (" << mDistanceRemaining << " tiles remaining)";
      SetFluffDescription(description.str());
    }
  }

  // Schedule the effect object for deletion.
  if(mSkillEffect != nullptr)
  {
    auto skillEffectObject = mSkillEffect->GetParent();
    if(skillEffectObject != nullptr)
    {
      skillEffectObject->ScheduleForDeletion();
      mSkillEffect = nullptr;
    }
  }
}

/******************************************************************************/
void MoveSkill::ProtectedCancel()
{
  mShortestPaths.clear();

  // Schedule the effect object for deletion.
  if(mSkillEffect != nullptr)
  {
    auto skillEffectObject = mSkillEffect->GetParent();
    if(skillEffectObject != nullptr)
    {
      skillEffectObject->ScheduleForDeletion();
      mSkillEffect = nullptr;
    }
  }
}

/******************************************************************************/
void MoveSkill::HandleEnabledChanged(bool aEnabled)
{
  // When enabled, update the distance remaining to the parent character's speed.
  if(aEnabled)
  {
    auto character = GetCharacter();
    if(character != nullptr)
    {
      auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        mDistanceRemaining = characterBehaviorComponent->GetSpeed();

        std::stringstream description;
        description << "Moves the character.";
        description << " (" << mDistanceRemaining << " tiles remaining)";
        SetFluffDescription(description.str());
      }
    }
  }
}
