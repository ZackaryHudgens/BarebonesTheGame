#include "EffectListBehaviorComponent.hpp"

#include <algorithm>

#include "Signals.hpp"

#include <iostream>

using Barebones::EffectListBehaviorComponent;

/******************************************************************************/
EffectListBehaviorComponent::EffectListBehaviorComponent()
  : Component()
  , mCharacter(nullptr)
  , mIconsPerRow(5)
  , mHorizontalPadding(0.1)
  , mVerticalPadding(0.1)
{
  EffectAddedToCharacter.Connect(*this, [this](CharacterBehaviorComponent& aCharacter,
                                               Effect& aEffect)
  {
    this->HandleEffectAddedToCharacter(aCharacter, aEffect);
  });

  EffectRemovedFromCharacter.Connect(*this, [this](CharacterBehaviorComponent& aCharacter,
                                                   Effect& aEffect)
  {
    this->HandleEffectRemovedFromCharacter(aCharacter, aEffect);
  });
}

/******************************************************************************/
void EffectListBehaviorComponent::Initialize()
{
  if(mCharacter != nullptr)
  {
    for(auto& effect : mCharacter->GetEffects())
    {
      if(effect != nullptr)
      {
        HandleEffectAddedToCharacter(*mCharacter, *effect);
      }
    }
  }
}

/******************************************************************************/
void EffectListBehaviorComponent::SetCharacter(CharacterBehaviorComponent& aCharacter)
{
  mCharacter = &aCharacter;

  for(auto& effect : mCharacter->GetEffects())
  {
    if(effect != nullptr)
    {
      HandleEffectAddedToCharacter(*mCharacter, *effect);
    }
  }
}

/******************************************************************************/
void EffectListBehaviorComponent::HandleEffectAddedToCharacter(CharacterBehaviorComponent& aCharacter,
                                                               Effect& aEffect)
{
  if(&aCharacter == mCharacter)
  {
    // Create a GameObject to hold the effect icon and add it as
    // a child, then reposition all the icons.
    auto mesh = aEffect.GetIcon();
    auto parent = GetParent();
    if(mesh != nullptr &&
       parent != nullptr)
    {
      auto newObject = std::make_unique<UrsineEngine::GameObject>(aEffect.GetName());
      newObject->SetScale(glm::vec3(0.1, 0.1, 1.0));
      newObject->AddComponent(std::move(mesh));
      parent->AddChild(std::move(newObject));

      mIcons.emplace_back(parent->GetChildren().back());

      RepositionIcons();
    }
  }
}

/******************************************************************************/
void EffectListBehaviorComponent::HandleEffectRemovedFromCharacter(CharacterBehaviorComponent& aCharacter,
                                                                   Effect& aEffect)
{
  if(&aCharacter == mCharacter)
  {
    // Remove the icon for this effect, then reposition all the icons.
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto findEffectObject = [aEffect](UrsineEngine::GameObject* aObject)
      {
        bool success = false;

        if(aObject != nullptr)
        {
          success = (aObject->GetName() == aEffect.GetName());
        }

        return success;
      };

      auto foundEffectObject = std::find_if(mIcons.begin(),
                                            mIcons.end(),
                                            findEffectObject);
      if(foundEffectObject != mIcons.end())
      {
        mIcons.erase(foundEffectObject);

        RepositionIcons();
      }
    }
  }
}

/******************************************************************************/
void EffectListBehaviorComponent::RepositionIcons()
{
  if(mCharacter != nullptr)
  {
    auto characterObject = mCharacter->GetParent();
    if(characterObject != nullptr)
    {
      auto characterMesh = characterObject->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
      if(characterMesh != nullptr)
      {
        // For each icon, place it above the character in a row.
        int numIconsInRow = 0;
        int numRows = 0;
        UrsineEngine::MeshComponent* previousIconMesh = nullptr;
        for(auto& iconObject : mIcons)
        {
          auto iconMesh = iconObject->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
          if(iconMesh != nullptr)
          {
            // Calculate this icon's x-position using the character's position
            // or the position of the previously placed icon.
            glm::vec3 iconPos;
            if(previousIconMesh != nullptr)
            {
              auto previousIconParent = previousIconMesh->GetParent();
              if(previousIconParent != nullptr)
              {
                iconPos = previousIconParent->GetPosition();
                iconPos.x += (previousIconMesh->GetWidth() / 2.0) + (iconMesh->GetWidth() / 2.0) + mHorizontalPadding;
              }
            }
            else
            {
              iconPos = characterObject->GetPosition();
              iconPos.x -= (characterMesh->GetWidth() / 2.0) - ((iconMesh->GetWidth() * 0.1) / 2.0);// - mHorizontalPadding;
            }

            // Calculate this icon's y-position using the number of rows.
            iconPos.y += (((iconMesh->GetHeight() * 0.1) / 2.0) + mVerticalPadding) * numRows;

            iconObject->SetPosition(iconPos);

            // Update the row count.
            ++numIconsInRow;
            if(numIconsInRow == mIconsPerRow)
            {
              previousIconMesh = nullptr;
              numIconsInRow = 0;
              ++numRows;
            }
            else
            {
              previousIconMesh = iconMesh;
            }
          }
        }
      }
    }
  }
}
