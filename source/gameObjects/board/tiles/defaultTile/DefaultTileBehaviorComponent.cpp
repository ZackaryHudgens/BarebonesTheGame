#include "DefaultTileBehaviorComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "TileMeshComponent.hpp"

using Barebones::DefaultTileBehaviorComponent;

/******************************************************************************/
DefaultTileBehaviorComponent::DefaultTileBehaviorComponent()
  : TileBehaviorComponent()
  , mHighlightColor(0.94, 0.89, 0.51, 1.0)
  , mHoverColor(0.43, 0.87, 0.87, 1.0)
  , mGlowSpeed(1.0)
  , mTimeBeganGlowing(0.0)
  , mScale(0.1)
  , mScaleSpeed(0.1)
  , mScaling(false)
{
}

/******************************************************************************/
void DefaultTileBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->SetScale(glm::vec3(mScale,
                               mScale,
                               mScale));
    mScaling = true;
  }
}

/******************************************************************************/
void DefaultTileBehaviorComponent::Update()
{
  // Scale the tile up to normal size.
  if(mScaling)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      // Calculate the new scalar value via interpolation.
      // Because we scale each axis evenly, we can just use
      // the x-axis scale as our starting point ([0, 0] in the matrix).
      auto transform = parent->GetScalarTransform();
      double scalar = transform[0][0];
      double newScalar = glm::mix(scalar, 1.0, mScaleSpeed);
      newScalar = std::min(newScalar, 1.0);

      parent->SetScale(glm::vec3(newScalar,
                                 newScalar,
                                 newScalar));
      if(newScalar == 1.0)
      {
        mScaling = false;
      }
    }
  }

  // Add a simple highlight effect to the tile.
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
          glm::vec4 color = mHighlightColor;
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
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto mesh = parent->GetFirstComponentOfType<TileMeshComponent>();
    if(mesh != nullptr)
    {
      auto shader = mesh->GetCurrentShader();
      if(shader != nullptr)
      {
        shader->Activate();
        if(aHovered)
        {
          shader->SetVec4("hoverColor", mHoverColor);
        }
        else
        {
          shader->SetVec4("hoverColor", glm::vec4(1.0,
                                                  1.0,
                                                  1.0,
                                                  1.0));
        }
      }
    }
  }
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
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto mesh = parent->GetFirstComponentOfType<TileMeshComponent>();
      if(mesh != nullptr)
      {
        auto shader = mesh->GetCurrentShader();
        if(shader != nullptr)
        {
          shader->Activate();
          shader->SetVec4("highlightColor", glm::vec4(1.0,
                                                      1.0,
                                                      1.0,
                                                      1.0));
        }
      }
    }
  }
}
