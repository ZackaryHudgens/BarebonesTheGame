#include "SpellMenuLayoutComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>
#include <SpriteComponent.hpp>

using Barebones::SpellMenuLayoutComponent;

/******************************************************************************/
SpellMenuLayoutComponent::SpellMenuLayoutComponent()
  : MenuLayoutComponent()
  , mSpellNameVerticalPadding(5)
  , mSpellDescriptionVerticalPadding(5)
  , mSpellNameHeight(100)
  , mSpellDescriptionHeight(500)
{
}

/******************************************************************************/
void SpellMenuLayoutComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a sprite for the spellbook and a GameObject to hold it.
    auto spellbookSprite = std::make_unique<UrsineEngine::SpriteComponent>();
    spellbookSprite->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    UrsineEngine::Texture texture;
    texture.CreateTextureFromFile("resources/sprites/spellbook.png");
    spellbookSprite->SetTexture(texture);

    std::string vertexFile = "resources/shaders/UIShader.vert";
    std::string fragmentFile = "resources/shaders/UIShader.frag";
    UrsineEngine::Shader shader(vertexFile, fragmentFile);
    spellbookSprite->AddShader("default", shader);
    spellbookSprite->SetCurrentShader("default");

    auto spellbookObject = std::make_unique<UrsineEngine::GameObject>("spellbook");
    spellbookObject->AddComponent(std::move(spellbookSprite));

    // Scale up the spellbook.
    spellbookObject->SetScale(glm::vec3(22.0, 22.0, 1.0));

    // Center the spellbook on the overlay.
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;
    double horizontalCenter = overlayWidth / 2.0;
    double verticalCenter = (overlayHeight / 2.0) - 50.0;
    spellbookObject->SetPosition(glm::vec3(horizontalCenter, verticalCenter, 0.1));

    parent->AddChild(std::move(spellbookObject));

    // Create two text boxes and GameObjects to hold them.
    auto spellNameObject = std::make_unique<UrsineEngine::GameObject>("spellNameObject");
    spellNameObject->AddComponent(std::make_unique<TextBoxComponent>());
    auto spellDescriptionObject = std::make_unique<UrsineEngine::GameObject>("spellDescriptionObject");
    spellDescriptionObject->AddComponent(std::make_unique<TextBoxComponent>());

    parent->AddChild(std::move(spellNameObject));
    mSpellNameTextBox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();
    parent->AddChild(std::move(spellDescriptionObject));
    mSpellDescriptionTextBox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();

    // Set the background texture for both text boxes.
    //UrsineEngine::Texture backgroundTexture;
    //backgroundTexture.CreateTextureFromFile("resources/sprites/menuBox.png");
    //mSpellNameTextBox->SetTexture(backgroundTexture);
    //mSpellDescriptionTextBox->SetTexture(backgroundTexture);

    // Set the font parameters for both text boxes.
    mSpellNameTextBox->SetFont("Alagard", "Medium");
    mSpellNameTextBox->SetTextSize(72);
    mSpellNameTextBox->SetTextAlignment(TextAlignment::eCENTER);
    mSpellNameTextBox->SetTextColor(glm::vec4(0.125, 0.125, 0.125, 1.0));
    mSpellNameTextBox->SetVerticalPadding(mSpellNameVerticalPadding);

    mSpellDescriptionTextBox->SetFont("Alagard", "Medium");
    mSpellDescriptionTextBox->SetTextSize(48);
    mSpellDescriptionTextBox->SetTextAlignment(TextAlignment::eCENTER);
    mSpellDescriptionTextBox->SetTextColor(glm::vec4(0.125, 0.125, 0.125, 1.0));
    mSpellDescriptionTextBox->SetVerticalPadding(mSpellDescriptionVerticalPadding);

    mSpellNameTextBox->SetWidth(500.0);
    mSpellNameTextBox->SetHeight(mSpellNameHeight);
    mSpellNameTextBox->SetFixedWidth(true);
    mSpellNameTextBox->SetFixedHeight(true);

    mSpellDescriptionTextBox->SetWidth(500.0);
    mSpellDescriptionTextBox->SetHeight(mSpellDescriptionHeight);
    mSpellDescriptionTextBox->SetFixedWidth(true);
    mSpellDescriptionTextBox->SetFixedHeight(true);

    mSpellNameTextBox->SetText("woohoo");
    mSpellNameTextBox->GetParent()->SetPosition(glm::vec3(500.0, 500.0, 0.2));
  }
}
