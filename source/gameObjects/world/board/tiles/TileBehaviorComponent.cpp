#include "TileBehaviorComponent.hpp"

#include <MeshComponent.hpp>

#include "Colors.hpp"
#include "Signals.hpp"

using Barebones::TileBehaviorComponent;

/******************************************************************************/
TileBehaviorComponent::TileBehaviorComponent()
  : Component()
  , mFadeValue(0.0)
  , mFadeSpeed(0.1)
  , mFadingIn(false)
{
}

/******************************************************************************/
void TileBehaviorComponent::Initialize()
{
  mFadingIn = true;
}

/******************************************************************************/
void TileBehaviorComponent::Update(double aTime)
{
  // Fade in the tile texture.
  if(mFadingIn)
  {
    auto newFadeValue = glm::mix(mFadeValue, 1.0f, mFadeSpeed);
    if((1.0 - newFadeValue) <= 0.005)
    {
      newFadeValue = 1.0;
      mFadingIn = false;
    }

    mFadeValue = newFadeValue;
    SetHighlightIntensity(1.0 - mFadeValue);

    auto parent = GetParent();
    if(parent != nullptr &&
       !mFadingIn)
    {
      TileReadyForUse.Notify(*parent);
    }
  }
}

/******************************************************************************/
void TileBehaviorComponent::SetHighlightColor(const glm::vec3& aColor)
{
  // Set the highlight color in the current shader, if there is one.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto meshComponent = parent->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(meshComponent != nullptr)
    {
      auto shader = meshComponent->GetCurrentShader();
      if(shader != nullptr)
      {
        shader->Activate();
        shader->SetVec4("highlightColor",
                        glm::vec4(aColor, 1.0));
      }
    }
  }
}

/******************************************************************************/
void TileBehaviorComponent::SetHighlightIntensity(double aIntensity)
{
  // Set the highlight color in the current shader, if there is one.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto meshComponent = parent->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(meshComponent != nullptr)
    {
      auto shader = meshComponent->GetCurrentShader();
      if(shader != nullptr)
      {
        shader->Activate();
        shader->SetFloat("highlightIntensity",
                         aIntensity);
      }
    }
  }
}
