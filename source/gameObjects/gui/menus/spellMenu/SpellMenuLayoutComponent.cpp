#include "SpellMenuLayoutComponent.hpp"

#include <algorithm>

#include <Environment.hpp>
#include <GameObject.hpp>

#include "SkillActionBehaviorComponent.hpp"

#include <iostream>

using Barebones::SpellMenuLayoutComponent;

/******************************************************************************/
SpellMenuLayoutComponent::SpellMenuLayoutComponent()
  : MenuLayoutComponent()
  , mSpellbookSprite(nullptr)
  , mSpellNameTextBox(nullptr)
  , mSpellDescriptionTextBox(nullptr)
  , mSpellbookScalar(25.0)
  , mSpellbookVerticalOffset(25)
  , mSpellNameHeight(100)
  , mSpellNameWidth(500)
  , mSpellNameVerticalPadding(5)
  , mSpellNameHorizontalOffset(375)
  , mSpellNameVerticalOffset(350)
  , mSpellDescriptionHeight(100)
  , mSpellDescriptionWidth(500)
  , mSpellDescriptionVerticalPadding(5)
  , mSpellDescriptionHorizontalOffset(375)
  , mSpellDescriptionVerticalOffset(350)
{
  // Store the three different texture clips for the spellbook.
  mFirstSpellClip.mHeight = 36;
  mFirstSpellClip.mWidth = 64;
  mFirstSpellClip.mX = 0;
  mFirstSpellClip.mY = 72;

  mLastSpellClip.mHeight = 36;
  mLastSpellClip.mWidth = 64;
  mLastSpellClip.mX = 0;
  mLastSpellClip.mY = 36;

  mCenterSpellClip.mHeight = 36;
  mCenterSpellClip.mWidth = 64;
  mCenterSpellClip.mX = 0;
  mCenterSpellClip.mY = 0;
}

/******************************************************************************/
void SpellMenuLayoutComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a sprite for the spellbook and a GameObject to hold it.
    auto spellbookObject = std::make_unique<UrsineEngine::GameObject>("spellbook");
    spellbookObject->AddComponent(std::make_unique<UrsineEngine::SpriteComponent>());
    spellbookObject->SetScale(glm::vec3(mSpellbookScalar,
                                        mSpellbookScalar,
                                        1.0));
    parent->AddChild(std::move(spellbookObject));
    mSpellbookSprite = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::SpriteComponent>();

    mSpellbookSprite->SetHasTransparency(false);
    mSpellbookSprite->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    UrsineEngine::Texture texture;
    texture.CreateTextureFromFile("resources/sprites/spellbook.png");
    mSpellbookSprite->SetTexture(texture);

    std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
    std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
    UrsineEngine::Shader texturedMeshShader(vertexFile, fragmentFile);
    mSpellbookSprite->AddShader("texturedMeshShader", texturedMeshShader);
    mSpellbookSprite->SetCurrentShader("texturedMeshShader");

    // Center the spellbook on the overlay.
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;
    double horizontalCenter = (overlayWidth / 2.0);
    double verticalCenter = (overlayHeight / 2.0);
    mSpellbookSprite->GetParent()->SetPosition(glm::vec3(horizontalCenter,
                                                         verticalCenter - mSpellbookVerticalOffset,
                                                         -0.1));

    // Create two text boxes and GameObjects to hold them.
    auto spellNameObject = std::make_unique<UrsineEngine::GameObject>("spellNameObject");
    spellNameObject->AddComponent(std::make_unique<TextBoxComponent>());
    auto spellDescriptionObject = std::make_unique<UrsineEngine::GameObject>("spellDescriptionObject");
    spellDescriptionObject->AddComponent(std::make_unique<TextBoxComponent>());

    parent->AddChild(std::move(spellNameObject));
    mSpellNameTextBox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();
    parent->AddChild(std::move(spellDescriptionObject));
    mSpellDescriptionTextBox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();

    // Set the font parameters for both text boxes.
    mSpellNameTextBox->SetFont("Alagard", "Medium");
    mSpellNameTextBox->SetTextSize(72);
    mSpellNameTextBox->SetTextAlignment(TextAlignment::eCENTER);
    mSpellNameTextBox->SetTextColor(glm::vec4(0.125, 0.125, 0.125, 1.0));
    mSpellNameTextBox->SetVerticalPadding(mSpellNameVerticalPadding);

    mSpellDescriptionTextBox->SetFont("Alagard", "Medium");
    mSpellDescriptionTextBox->SetTextSize(48);
    mSpellDescriptionTextBox->SetTextAlignment(TextAlignment::eLEFT);
    mSpellDescriptionTextBox->SetTextColor(glm::vec4(0.125, 0.125, 0.125, 1.0));
    mSpellDescriptionTextBox->SetVerticalPadding(mSpellDescriptionVerticalPadding);

    mSpellNameTextBox->SetWidth(mSpellNameWidth);
    mSpellNameTextBox->SetHeight(mSpellNameHeight);
    mSpellNameTextBox->SetFixedWidth(true);
    mSpellNameTextBox->SetFixedHeight(true);

    mSpellDescriptionTextBox->SetWidth(mSpellDescriptionWidth);
    mSpellDescriptionTextBox->SetHeight(mSpellDescriptionHeight);
    mSpellDescriptionTextBox->SetFixedWidth(true);
    mSpellDescriptionTextBox->SetFixedHeight(true);

    // Place the text boxes on the spellbook.
    auto spellbookPos = mSpellbookSprite->GetParent()->GetPosition();
    mSpellNameTextBox->GetParent()->SetPosition(glm::vec3(spellbookPos.x - mSpellNameHorizontalOffset,
                                                          spellbookPos.y + mSpellNameVerticalOffset,
                                                          0.1));
    mSpellDescriptionTextBox->GetParent()->SetPosition(glm::vec3(spellbookPos.x + mSpellDescriptionHorizontalOffset,
                                                                 spellbookPos.y + mSpellDescriptionVerticalOffset,
                                                                 0.1));
  }
}

/******************************************************************************/
void SpellMenuLayoutComponent::HandleActionAdded()
{
  // If this is the only action, switch the sprite to display the first spell.
  if(GetActions().size() == 1)
  {
    mSpellbookSprite->SetRenderDimensions(mFirstSpellClip);
  }
}

/******************************************************************************/
void SpellMenuLayoutComponent::HandleActionHovered()
{
  auto action = GetCurrentlyHoveredAction();
  if(action != nullptr)
  {
    // Update the spell name and description.
    auto skillAction = action->GetFirstComponentOfType<SkillActionBehaviorComponent>();
    if(skillAction != nullptr)
    {
      auto skill = skillAction->GetSkill();
      if(skill != nullptr &&
         mSpellNameTextBox != nullptr &&
         mSpellDescriptionTextBox != nullptr)
      {
        mSpellNameTextBox->SetText(skill->GetName());
        mSpellDescriptionTextBox->SetText(skill->GetDescription());
      }
    }

    // Update the sprite based on the position of the current action
    // in the action list.
    auto actions = GetActions();
    auto foundAction = std::find(actions.begin(),
                                 actions.end(),
                                 action);
    if(foundAction != actions.end())
    {
      if((*foundAction) == actions.front())
      {
        mSpellbookSprite->SetRenderDimensions(mFirstSpellClip);
      }
      else if((*foundAction) == actions.back())
      {
        mSpellbookSprite->SetRenderDimensions(mLastSpellClip);
      }
      else
      {
        mSpellbookSprite->SetRenderDimensions(mCenterSpellClip);
      }
    }
  }
}

/******************************************************************************/
void SpellMenuLayoutComponent::HandleActionExecuted()
{
  // When a skill is executed, this menu is no longer needed.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->ScheduleForDeletion();
  }
}
