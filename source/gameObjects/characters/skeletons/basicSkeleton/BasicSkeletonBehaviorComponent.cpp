#include "BasicSkeletonBehaviorComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "BoardLayoutComponent.hpp"
#include "CharacterSpriteComponent.hpp"

#include "DefendSkillComponent.hpp"
#include "SlashSkillComponent.hpp"

using Barebones::BasicSkeletonBehaviorComponent;

/******************************************************************************/
BasicSkeletonBehaviorComponent::BasicSkeletonBehaviorComponent()
  : CharacterBehaviorComponent()
  , mHorizontalMovement(2)
  , mVerticalMovement(2)
{
  SetMaximumHealth(10);
  SetCurrentHealth(10);
}

/******************************************************************************/
Barebones::TileList BasicSkeletonBehaviorComponent::GetMovements(UrsineEngine::GameObject& aObject,
                                                                 const TileLocation& aLocation) const
{
  TileList moves;

  auto layout = aObject.GetFirstComponentOfType<BoardLayoutComponent>();
  if(layout != nullptr)
  {
    TileLocation moveLocation = aLocation;

    // Determine movements to the left.
    for(int left = 0; left < mHorizontalMovement; ++left)
    {
      moveLocation.first = aLocation.first - left - 1;

      if(layout->GetCharacterAtLocation(moveLocation) == nullptr)
      {
        // Add this location to the move list.
        moves.emplace_back(moveLocation);
      }
      else
      {
        // If there is a character at this location,
        // we can no longer move left.
        break;
      }
    }
    moveLocation.first = aLocation.first;

    // Determine movements to the right.
    for(int right = 0; right < mHorizontalMovement; ++right)
    {
      moveLocation.first = aLocation.first + right + 1;

      if(layout->GetCharacterAtLocation(moveLocation) == nullptr)
      {
        // Add this location to the move list.
        moves.emplace_back(moveLocation);
      }
      else
      {
        // If there is a character at this location,
        // we can no longer move right.
        break;
      }
    }
    moveLocation.first = aLocation.first;

    // Determine upward movements.
    for(int up = 0; up < mVerticalMovement; ++up)
    {
      moveLocation.second = aLocation.second + up + 1;

      if(layout->GetCharacterAtLocation(moveLocation) == nullptr)
      {
        // Add this location to the move list.
        moves.emplace_back(moveLocation);
      }
      else
      {
        // If there is a character at this location,
        // we can no longer move up.
        break;
      }
    }
    moveLocation.second = aLocation.second;

    // Determine downward movements.
    for(int down = 0; down < mVerticalMovement; ++down)
    {
      moveLocation.second = aLocation.second - down - 1;

      if(layout->GetCharacterAtLocation(moveLocation) == nullptr)
      {
        // Add this location to the move list.
        moves.emplace_back(moveLocation);
      }
      else
      {
        // If there is a character at this location,
        // we can no longer move down.
        break;
      }
    }
  }

  return moves;
}

/******************************************************************************/
void BasicSkeletonBehaviorComponent::ProtectedUpdate()
{
}

/******************************************************************************/
void BasicSkeletonBehaviorComponent::AddSkills()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->AddComponent(std::make_unique<SlashSkillComponent>());
    parent->AddComponent(std::make_unique<DefendSkillComponent>());
  }
}
