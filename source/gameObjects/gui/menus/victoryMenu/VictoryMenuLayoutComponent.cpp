#include "VictoryMenuLayoutComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "TextBoxComponent.hpp"

#include "Colors.hpp"
#include "Fonts.hpp"

using Barebones::VictoryMenuLayoutComponent;

/******************************************************************************/
VictoryMenuLayoutComponent::VictoryMenuLayoutComponent()
  : MainMenuLayoutComponent()
{
}

/******************************************************************************/
void VictoryMenuLayoutComponent::SetActToLoad(const Act& aAct)
{
  // Create a new action that loads a scene for the given act.
  auto newAction = std::make_unique<MenuAction>("ContinueAction");
  AddAction(std::move(newAction));
}

/******************************************************************************/
void VictoryMenuLayoutComponent::ProtectedInitialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Add a "Victory!" text box to the parent.
    auto textBoxObject = std::make_unique<UrsineEngine::GameObject>("VictoryTextBox");
    textBoxObject->AddComponent(std::make_unique<TextBoxComponent>());
    auto textBox = parent->GetFirstComponentOfType<TextBoxComponent>();

    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/gui/menuBox.png");
    textBox->SetTexture(backgroundTexture);

    textBox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    textBox->SetTextSize(BIGGEST_FONT_SIZE);
    textBox->SetTextAlignment(TextAlignment::eCENTER);

    auto textShader = textBox->GetTextShader();
    if(textShader != nullptr)
    {
      textShader->Activate();
      textShader->SetVec4("textColor", (glm::vec4(BACKGROUND_COLOR, 1.0)));
    }

    textBox->SetVerticalPadding(25);

    // Set the dimensions of the text box so that it stretches
    // across the screen.
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    textBox->SetWidth(overlayWidth);
    textBox->SetHeight(150);
    textBox->SetFixedWidth(true);
    textBox->SetFixedHeight(true);

    textBox->SetText("Victory!");

    // Center the display on the screen.
    double horizontalCenter = overlayWidth / 2.0;
    textBoxObject->SetPosition(glm::vec3(horizontalCenter,
                                         overlayHeight - (150 / 2.0),
                                         0.0));
    parent->AddChild(std::move(textBoxObject));
  }

  MainMenuLayoutComponent::ProtectedInitialize();
}
