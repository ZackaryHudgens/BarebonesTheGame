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
  }
}
