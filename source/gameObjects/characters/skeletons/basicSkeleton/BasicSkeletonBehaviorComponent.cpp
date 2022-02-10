#include "BasicSkeletonBehaviorComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "BoardLayoutComponent.hpp"
#include "CharacterSpriteComponent.hpp"

using Barebones::BasicSkeletonBehaviorComponent;

/******************************************************************************/
BasicSkeletonBehaviorComponent::BasicSkeletonBehaviorComponent()
  : CharacterBehaviorComponent()
  , mGlowSpeed(1.0)
  , mTimeBeganGlowing(0.0)
  , mHorizontalMovement(2)
  , mVerticalMovement(2)
{
}

/******************************************************************************/
Barebones::TileList BasicSkeletonBehaviorComponent::GetMovements(UrsineEngine::GameObject& aObject,
                                                                 const TileLocation& aLocation) const
{
  TileList moves;

  auto layout = aObject.GetFirstComponentOfType<BoardLayoutComponent>();
  if(layout != nullptr)
  {
    TileLocation moveLocation;
    moveLocation.first = aLocation.first;
    moveLocation.second = aLocation.second;

    // Determine movements to the left.
    for(int left = 0; left < mHorizontalMovement; ++left)
    {
      moveLocation.first = aLocation.first - left - 1;

      if(layout->GetCharacterAtPosition(moveLocation.first,
                                        moveLocation.second) == nullptr)
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

      if(layout->GetCharacterAtPosition(moveLocation.first,
                                        moveLocation.second) == nullptr)
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

      if(layout->GetCharacterAtPosition(moveLocation.first,
                                        moveLocation.second) == nullptr)
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

      if(layout->GetCharacterAtPosition(moveLocation.first,
                                        moveLocation.second) == nullptr)
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
  if(IsSelected())
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto sprite = parent->GetFirstComponentOfType<CharacterSpriteComponent>();
      if(sprite != nullptr)
      {
        auto shader = sprite->GetCurrentShader();
        if(shader != nullptr)
        {
          double timeSpentGlowing = env.GetTime() - mTimeBeganGlowing;
          glm::vec4 color = glm::vec4(1.0,
                                      1.0,
                                      0.0,
                                      1.0);

          if(timeSpentGlowing > (mGlowSpeed / 2.0))
          {
            // The glow is fading.
            color.x = 0.8;
            color.y = 0.8;
          }
          else
          {
            // The glow is increasing.
            color.x = 1.0;
            color.y = 1.0;
          }

          shader->Activate();
          shader->SetVec4("selectionColor", color);

          if(timeSpentGlowing > mGlowSpeed)
          {
            mTimeBeganGlowing = env.GetTime();
          }
        }
      }
    }
  }
}

/******************************************************************************/
void BasicSkeletonBehaviorComponent::HandleSelectionChanged(bool aSelected)
{
  if(aSelected)
  {
    mTimeBeganGlowing = env.GetTime();
  }
  else
  {
    // If this skeleton was deselected, restore the sprite component
    // to its normal color.
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto sprite = parent->GetFirstComponentOfType<CharacterSpriteComponent>();
      if(sprite != nullptr)
      {
        auto shader = sprite->GetCurrentShader();
        if(shader != nullptr)
        {
          shader->Activate();
          shader->SetVec4("selectionColor", glm::vec4(1.0,
                                                      1.0,
                                                      1.0,
                                                      1.0));
        }
      }
    }
  }
}
