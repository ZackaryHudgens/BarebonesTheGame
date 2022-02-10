#include "DefaultTileBehaviorComponent.hpp"

#include <GameObject.hpp>

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

  // Add a simple glow effect to the tile.
  if(IsHighlighted())
  {
  }
}

/******************************************************************************/
void DefaultTileBehaviorComponent::HandleHighlightChanged(bool aHighlighted)
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
        shader->SetVec4("highlightColor", glm::vec4(GetHighlightColor(),
                                                    1.0));
      }
    }
  }
}
