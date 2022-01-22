#include "BasicSkeletonBehaviorComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "CharacterSpriteComponent.hpp"

#include <iostream>

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
void BasicSkeletonBehaviorComponent::Update()
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
Barebones::MoveList BasicSkeletonBehaviorComponent::GetMovements(const TileLocation& aLocation) const
{
  MoveList moves;
  TileLocation moveLocation;

  for(int h = mHorizontalMovement * 2; h > 0; --h)
  {
    if(h <= mHorizontalMovement)
    {
      // Add moves to the left.
      moveLocation.first = aLocation.first - h;
      moveLocation.second = aLocation.second;
    }
    else
    {
      // Add moves to the right.
      moveLocation.first = aLocation.first + (h - mHorizontalMovement);
      moveLocation.second = aLocation.second;
    }

    moves.emplace_back(moveLocation);
  }

  for(int v = mVerticalMovement * 2; v > 0; --v)
  {
    if(v <= mVerticalMovement)
    {
      // Add moves to the bottom.
      moveLocation.first = aLocation.first;
      moveLocation.second = aLocation.second - v;
    }
    else
    {
      // Add moves to the top.
      moveLocation.first = aLocation.first;
      moveLocation.second = aLocation.second + (v - mVerticalMovement);
    }

    moves.emplace_back(moveLocation);
  }

  return moves;
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
