#include "DesecratedTileBehaviorComponent.hpp"

#include <GameObject.hpp>
#include <MeshComponent.hpp>

#include "CharacterBehaviorComponent.hpp"

#include "Signals.hpp"

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
void DesecratedTileBehaviorComponent::HandleTurnEnded(UrsineEngine::GameObject& aCharacter)
{
  auto characterBehaviorComponent = aCharacter.GetFirstComponentOfType<CharacterBehaviorComponent>();
  if(characterBehaviorComponent != nullptr)
  {
    switch(characterBehaviorComponent->GetType())
    {
      case Type::eHUMAN:
      {
        characterBehaviorComponent->DealDamage(2);
        break;
      }
      case Type::eSKELETON:
      {
        characterBehaviorComponent->DealDamage(-2);
        break;
      }
      default:
      {
        break;
      }
    }
  }
}

/******************************************************************************/
void DesecratedTileBehaviorComponent::HandleHighlightChanged(bool aHighlight)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto mesh = parent->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
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
    auto mesh = parent->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
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
