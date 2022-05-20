#include "MainMenuLayoutComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>

#include "Colors.hpp"

using Barebones::MainMenuLayoutComponent;

/******************************************************************************/
MainMenuLayoutComponent::MainMenuLayoutComponent()
  : MenuLayoutComponent()
  , mHoveredTextBox(nullptr)
  , mVerticalPadding(50)
{
}

/******************************************************************************/
void MainMenuLayoutComponent::HandleActionAdded()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto newAction = GetActions().back();

    // Create a new GameObject with a TextBoxComponent, then add it as a child.
    auto actionObject = std::make_unique<UrsineEngine::GameObject>(newAction->GetName());
    actionObject->AddComponent(std::make_unique<TextBoxComponent>());
    parent->AddChild(std::move(actionObject));

    auto newActionTextBox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();

    // Set the font parameters for this text box.
    newActionTextBox->SetFont("Alagard", "Medium");
    newActionTextBox->SetTextSize(48);
    newActionTextBox->SetTextAlignment(TextAlignment::eCENTER);
    newActionTextBox->SetTextColor(glm::vec4(DARK_COLOR, 1.0));
    newActionTextBox->SetWidth(500);
    newActionTextBox->SetFixedWidth(true);

    newActionTextBox->SetText(newAction->GetName());

    // Position the text box in the center of the screen.
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;
    double xPos = overlayWidth / 2.0;
    double yPos = overlayHeight / 2.0;

    yPos -= (mVerticalPadding * mTextBoxes.size());

    newActionTextBox->GetParent()->SetPosition(glm::vec3(xPos, yPos, 0.1));
    mTextBoxes.emplace_back(newActionTextBox);
  }
}

/******************************************************************************/
void MainMenuLayoutComponent::HandleActionHovered()
{
}

/******************************************************************************/
void MainMenuLayoutComponent::HandleActionExecuted()
{
}
