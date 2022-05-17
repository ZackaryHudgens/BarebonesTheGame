#include "MoveSkill.hpp"

#include <algorithm>
#include <sstream>

#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

using Barebones::MoveSkill;

/******************************************************************************/
MoveSkill::MoveSkill(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
  , mSkillEffect(nullptr)
  , mDistanceRemaining(0)
{
  SetName("Move");
  SetDescription("Moves the character.");

  // Initialize the distance remaining if possible.
  auto characterBehaviorComponent = aParent.GetFirstComponentOfType<CharacterBehaviorComponent>();
  if(characterBehaviorComponent != nullptr)
  {
    mDistanceRemaining = characterBehaviorComponent->GetSpeed();

    std::stringstream description;
    description << GetDescription();
    description << " (" << mDistanceRemaining << " tiles remaining)";
    SetDescription(description.str());
  }
}

/******************************************************************************/
void MoveSkill::Select()
{
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
  }
}

/******************************************************************************/
void MoveSkill::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                 const TileLocation& aLocation)
{
  auto parent = GetParent();
  auto characterBehaviorComponent = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(characterBehaviorComponent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());

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

    // Find the shortest path to aLocation, then move the character along it.
    if(mShortestPaths.empty())
    {
      mShortestPaths = characterBehaviorComponent->GenerateShortestPathList(aBoard, characterLocation);
    }

    auto path = std::find_if(mShortestPaths.begin(),
                             mShortestPaths.end(),
                             isPath);
    if(path != mShortestPaths.end())
    {
      boardLayoutComponent->MoveCharacterAlongPath(characterLocation,
                                                   path->first);

      // After moving the character, the shortest path list will need to be
      // regenerated on the next Execute().
      mShortestPaths.clear();

      // Subtract the shortest distance from the distance remaining. If no distance
      // remains, disable this skill.
      mDistanceRemaining -= path->second;
      if(mDistanceRemaining <= 0)
      {
        SetEnabled(false);
      }

      std::stringstream description;
      description << "Moves the character.";
      description << " (" << mDistanceRemaining << " tiles remaining)";
      SetDescription(description.str());
    }
  }

  mSkillEffect = nullptr;
}

/******************************************************************************/
Barebones::TileList MoveSkill::GetValidTiles(UrsineEngine::GameObject& aBoard)
{
  TileList tiles;

  auto parent = GetParent();
  auto characterBehaviorComponent = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(characterBehaviorComponent != nullptr &&
     boardLayoutComponent != nullptr)
  {
    auto characterLocation = boardLayoutComponent->GetLocationOfCharacter(parent->GetName());

    if(mShortestPaths.empty())
    {
      mShortestPaths = characterBehaviorComponent->GenerateShortestPathList(aBoard, characterLocation);
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

    if(mSkillEffect != nullptr)
    {
      mSkillEffect->SetBoard(aBoard);
      mSkillEffect->SetShortestPathList(mShortestPaths);
    }
  }

  return tiles;
}

/******************************************************************************/
void MoveSkill::HandleEnabledChanged(bool aEnabled)
{
  // When enabled, update the distance remaining to the parent character's speed.
  if(aEnabled)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto characterBehaviorComponent = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
      if(characterBehaviorComponent != nullptr)
      {
        mDistanceRemaining = characterBehaviorComponent->GetSpeed();

        std::stringstream description;
        description << "Moves the character.";
        description << " (" << mDistanceRemaining << " tiles remaining)";
        SetDescription(description.str());
      }
    }
  }
}
