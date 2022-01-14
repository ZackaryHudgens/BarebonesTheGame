#include "DefaultTileBehaviorComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "TileMeshComponent.hpp"

using Barebones::DefaultTileBehaviorComponent;

/******************************************************************************/
DefaultTileBehaviorComponent::DefaultTileBehaviorComponent()
  : TileBehaviorComponent()
  , mGlowSpeed(1.0)
  , mTimeBeganGlowing(0.0)
{
}

/******************************************************************************/
void DefaultTileBehaviorComponent::Update()
{
  if(IsHighlighted())
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto mesh = parent->GetFirstComponentOfType<TileMeshComponent>();
      if(mesh != nullptr)
      {
        auto shader = mesh->GetCurrentShader();
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
          shader->SetVec4("highlightColor", color);

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
void DefaultTileBehaviorComponent::HandleHoverChanged(bool aHovered)
{
}

/******************************************************************************/
void DefaultTileBehaviorComponent::HandleHighlightChanged(bool aHighlighted)
{
  if(aHighlighted)
  {
    mTimeBeganGlowing = env.GetTime();
  }
  else
  {
    // If this skeleton was deselected, restore the sprite component
    // to its normal color.
  }
}
