#include "EffectListBehaviorComponent.hpp"

#include <algorithm>

#include "Signals.hpp"

using Barebones::EffectListBehaviorComponent;

/******************************************************************************/
EffectListBehaviorComponent::EffectListBehaviorComponent()
  : Component()
  , mCharacter(nullptr)
  , mIconsPerRow(5)
  , mHorizontalPadding(0.1)
  , mVerticalPadding(0.1)
  , mIconScale(0.3)
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
  // On initialization, add an effect icon for each effect on the set character.
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

  // Remove each effect icon from the parent object.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    for(auto& icon : mIcons)
    {
      parent->RemoveChild(icon->GetName());
    }
  }

  mIcons.clear();

  // Add an effect icon for each effect on the set character.
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
    // a child object, then reposition all the icons.
    auto mesh = aEffect.GetIcon();
    auto parent = GetParent();
    if(mesh != nullptr &&
       parent != nullptr)
    {
      mesh->SetRenderOption(GL_DEPTH_TEST, false);

      auto newObject = std::make_unique<UrsineEngine::GameObject>(aEffect.GetName());
      newObject->SetScale(glm::vec3(mIconScale, mIconScale, 1.0));
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
    auto parent = GetParent();
    if(parent != nullptr)
    {
      // Remove the icon for this effect, then reposition all the icons.
      auto findEffectObject = [aEffect](UrsineEngine::GameObject* aObject)
      {
        return aObject->GetName() == aEffect.GetName();
      };

      auto foundEffectObject = std::find_if(mIcons.begin(),
                                            mIcons.end(),
                                            findEffectObject);
      if(foundEffectObject != mIcons.end())
      {
        parent->RemoveChild((*foundEffectObject)->GetName());
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
            glm::vec3 iconPos(0.0, 0.0, 0.0);
            double iconHalfWidth = (iconMesh->GetWidth() / 2.0) * mIconScale;
            double iconHalfHeight = (iconMesh->GetHeight() / 2.0) * mIconScale;

            if(previousIconMesh != nullptr)
            {
              auto previousIconParent = previousIconMesh->GetParent();
              if(previousIconParent != nullptr)
              {
                double previousIconHalfWidth = previousIconMesh->GetWidth() / 2.0;

                iconPos = previousIconParent->GetPosition();
                iconPos.x += previousIconHalfWidth + iconHalfWidth + mHorizontalPadding;
              }
            }
            else
            {
              double characterMeshHalfWidth = characterMesh->GetWidth() / 2.0;

              auto parent = GetParent();
              if(parent != nullptr)
              {
                iconPos = parent->GetPosition();
              }

              iconPos.x -= (characterMeshHalfWidth - iconHalfWidth);
            }

            // Calculate this icon's y-position using the number of rows.
            iconPos.y += (iconHalfHeight + mVerticalPadding) * numRows;

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
