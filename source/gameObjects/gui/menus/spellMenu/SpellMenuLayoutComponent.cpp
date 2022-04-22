#include "SpellMenuLayoutComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "SkillActionBehaviorComponent.hpp"

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

    std::string vertexFile = "resources/shaders/UIShader.vert";
    std::string fragmentFile = "resources/shaders/UIShader.frag";
    UrsineEngine::Shader shader(vertexFile, fragmentFile);
    mSpellbookSprite->AddShader("default", shader);
    mSpellbookSprite->SetCurrentShader("default");

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
    mSpellNameTextBox->SetText("Woohoo");
    mSpellNameTextBox->GetParent()->SetPosition(glm::vec3(spellbookPos.x - mSpellNameHorizontalOffset,
                                                          spellbookPos.y + mSpellNameVerticalOffset,
                                                          0.1));

    mSpellDescriptionTextBox->SetText("Lorem ipsum dolor sit amet");
    mSpellDescriptionTextBox->GetParent()->SetPosition(glm::vec3(spellbookPos.x + mSpellDescriptionHorizontalOffset,
                                                                 spellbookPos.y + mSpellDescriptionVerticalOffset,
                                                                 0.1));
  }
}

/******************************************************************************/
void SpellMenuLayoutComponent::HandleActionAdded()
{
}

/******************************************************************************/
void SpellMenuLayoutComponent::HandleActionHovered()
{
  auto action = GetCurrentlyHoveredAction();
  if(action != nullptr)
  {
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
  }
}

/******************************************************************************/
void SpellMenuLayoutComponent::HandleActionSelected()
{
  // When a skill is selected, this menu is no longer needed.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->ScheduleForDeletion();
  }
}
