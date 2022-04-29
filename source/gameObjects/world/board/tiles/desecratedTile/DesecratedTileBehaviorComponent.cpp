#include "DesecratedTileBehaviorComponent.hpp"

#include <GameObject.hpp>

#include "Signals.hpp"

#include "TileMeshComponent.hpp"

using Barebones::DesecratedTileBehaviorComponent;

/******************************************************************************/
DesecratedTileBehaviorComponent::DesecratedTileBehaviorComponent()
  : TileBehaviorComponent()
  , mFadeValue(0.0)
  , mFadeSpeed(0.1)
  , mFadingIn(false)
{
}

/******************************************************************************/
void DesecratedTileBehaviorComponent::Initialize()
{
  mFadingIn = true;
}

/******************************************************************************/
void DesecratedTileBehaviorComponent::Update(double aTime)
{
  // Fade in the tile texture.
  if(mFadingIn)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto tileMesh = parent->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
      if(tileMesh != nullptr)
      {
        auto shader = tileMesh->GetCurrentShader();
        if(shader != nullptr)
        {
          if(shader->IsUniformDefined("fadeValue"))
          {
            shader->Activate();

            auto newFadeValue = glm::mix(mFadeValue, 1.0f, mFadeSpeed);
            if((1.0 - newFadeValue) <= 0.005)
            {
              newFadeValue = 1.0;
              mFadingIn = false;
            }

            mFadeValue = newFadeValue;
            shader->SetFloat("fadeValue", mFadeValue);
            if(!mFadingIn)
            {
              TileReadyForUse.Notify(*parent);
            }
          }
        }
      }
    }
  }
}

/******************************************************************************/
void DesecratedTileBehaviorComponent::HandleCharacterEntered(UrsineEngine::GameObject& aCharacter)
{
}

/******************************************************************************/
void DesecratedTileBehaviorComponent::HandleCharacterExited(UrsineEngine::GameObject& aCharacter)
{
}

/******************************************************************************/
void DesecratedTileBehaviorComponent::HandleHighlightChanged(bool aHighlight)
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
void DesecratedTileBehaviorComponent::HandleHoverChanged(bool aHover)
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