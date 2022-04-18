#include "DefaultTileBehaviorComponent.hpp"

#include <GameObject.hpp>

#include "Signals.hpp"

#include "TileMeshComponent.hpp"

using Barebones::DefaultTileBehaviorComponent;

/******************************************************************************/
DefaultTileBehaviorComponent::DefaultTileBehaviorComponent()
  : TileBehaviorComponent()
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
void DefaultTileBehaviorComponent::Update(double aTime)
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

      if((1.0 - newScalar) <= 0.005)
      {
        newScalar = 1.0;
      }

      parent->SetScale(glm::vec3(newScalar,
                                 newScalar,
                                 newScalar));

      if(newScalar == 1.0)
      {
        mScaling = false;
        TileReadyForUse.Notify(*parent);
      }
    }
  }

  // Add a simple glow effect to the tile.
  if(IsHighlighted())
  {
  }
}

/******************************************************************************/
void DefaultTileBehaviorComponent::HandleHighlightChanged(bool aHighlight)
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

        if(aHighlight)
        {
          shader->SetVec4("highlightColor", glm::vec4(GetHighlightColor(),
                                                      1.0));
        }
        else
        {
          shader->SetVec4("highlightColor", glm::vec4(1.0,
                                                      1.0,
                                                      1.0,
                                                      1.0));
        }
      }
    }
  }
}

/******************************************************************************/
void DefaultTileBehaviorComponent::HandleHoverChanged(bool aHover)
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

        if(aHover)
        {
          shader->SetVec4("hoverColor", glm::vec4(GetHoverColor(),
                                                  1.0));
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
