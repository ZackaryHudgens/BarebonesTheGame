#include "ColorChangeVisualEffectBehaviorComponent.hpp"

#include <MeshComponent.hpp>

#include "Signals.hpp"

using Barebones::ColorChangeVisualEffectBehaviorComponent;

/******************************************************************************/
ColorChangeVisualEffectBehaviorComponent::ColorChangeVisualEffectBehaviorComponent(UrsineEngine::GameObject& aCharacter,
                                                                                   const glm::vec3& aColor,
                                                                                   double aSpeed)
  : Component()
  , mCharacter(&aCharacter)
  , mColor(aColor)
  , mSpeed(aSpeed)
  , mFadeValue(0.0)
  , mFadingIn(true)
{
  auto characterMesh = mCharacter->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
  if(characterMesh != nullptr)
  {
    auto shader = characterMesh->GetCurrentShader();
    if(shader != nullptr)
    {
      shader->Activate();
      shader->SetVec4("fadeColor", glm::vec4(mColor, 1.0));
    }
  }
}

/******************************************************************************/
void ColorChangeVisualEffectBehaviorComponent::Update(double aTime)
{
  if(mCharacter != nullptr)
  {
    auto characterMesh = mCharacter->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(characterMesh != nullptr)
    {
      auto shader = characterMesh->GetCurrentShader();
      if(shader != nullptr)
      {
        if(mFadingIn)
        {
          mFadeValue += mSpeed;
          if(mFadeValue >= 1.0)
          {
            mFadingIn = false;

            auto parent = GetParent();
            if(parent != nullptr)
            {
              SkillExecuteRequestedFromVisualEffect.Notify(*parent);
            }
          }
        }
        else
        {
          mFadeValue -= mSpeed;
          if(mFadeValue <= 0.0)
          {
            auto parent = GetParent();
            if(parent != nullptr)
            {
              parent->ScheduleForDeletion();
            }
          }
        }

        shader->Activate();
        shader->SetFloat("fadeValue", mFadeValue);
      }
    }
  }
}
