#include "MoveSkill.hpp"

#include <algorithm>
#include <sstream>

#include <iostream>

#include "BoardLayoutComponent.hpp"
#include "CharacterBehaviorComponent.hpp"

using Barebones::MoveSkill;

/******************************************************************************/
MoveSkill::MoveSkill(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
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

    // Subtract the shortest distance from the distance remaining. If no distance
    // remains, disable this skill.
    auto shortestPaths = characterBehaviorComponent->GenerateShortestPathList(aBoard, characterLocation);
    auto path = std::find_if(shortestPaths.begin(),
                             shortestPaths.end(),
                             isPath);
    if(path != shortestPaths.end())
    {
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

    boardLayoutComponent->MoveCharacter(characterLocation,
                                        aLocation);
  }
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
    auto shortestPaths = characterBehaviorComponent->GenerateShortestPathList(aBoard, characterLocation);

    for(const auto& shortestPath : shortestPaths)
    {
      if(shortestPath.second <= mDistanceRemaining)
      {
        for(const auto& tile : shortestPath.first)
        {
          tiles.emplace_back(tile);
        }
      }
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
