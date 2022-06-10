#include "SkillMenuLayoutComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>
#include <SpriteComponent.hpp>

#include "Colors.hpp"

using Barebones::SkillMenuLayoutComponent;

/******************************************************************************/
SkillMenuLayoutComponent::SkillMenuLayoutComponent()
  : MenuLayoutComponent()
  , mSkillNameTextBox(nullptr)
  , mSkillDescriptionTextBox(nullptr)
  , mSkillNameHeight(100)
  , mSkillNameVerticalPadding(25)
  , mSkillDescriptionHeight(65)
  , mSkillDescriptionVerticalPadding(20)
{
}

/******************************************************************************/
void SkillMenuLayoutComponent::ProtectedInitialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create two text boxes and GameObjects to hold them.
    auto skillNameObject = std::make_unique<UrsineEngine::GameObject>("skillNameObject");
    skillNameObject->AddComponent(std::make_unique<TextBoxComponent>());
    auto skillDescriptionObject = std::make_unique<UrsineEngine::GameObject>("skillDescriptionObject");
    skillDescriptionObject->AddComponent(std::make_unique<TextBoxComponent>());

    parent->AddChild(std::move(skillNameObject));
    mSkillNameTextBox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();
    parent->AddChild(std::move(skillDescriptionObject));
    mSkillDescriptionTextBox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();

    // Set the background texture for both text boxes.
    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/gui/menuBox.png");
    mSkillNameTextBox->SetTexture(backgroundTexture);
    mSkillDescriptionTextBox->SetTexture(backgroundTexture);

    // Set the font parameters for both text boxes.
    mSkillNameTextBox->SetFont("Alagard", "Medium");
    mSkillNameTextBox->SetTextSize(72);
    mSkillNameTextBox->SetTextAlignment(TextAlignment::eCENTER);
    mSkillNameTextBox->SetVerticalPadding(mSkillNameVerticalPadding);

    auto skillTextShader = mSkillNameTextBox->GetTextShader();
    if(skillTextShader != nullptr)
    {
      skillTextShader->Activate();
      skillTextShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    }

    mSkillDescriptionTextBox->SetFont("Alagard", "Medium");
    mSkillDescriptionTextBox->SetTextSize(48);
    mSkillDescriptionTextBox->SetTextAlignment(TextAlignment::eCENTER);
    mSkillDescriptionTextBox->SetVerticalPadding(mSkillDescriptionVerticalPadding);

    auto descriptionTextShader = mSkillNameTextBox->GetTextShader();
    if(descriptionTextShader != nullptr)
    {
      descriptionTextShader->Activate();
      descriptionTextShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    }

    // Make both text boxes stretch across the screen.
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    mSkillNameTextBox->SetWidth(overlayWidth);
    mSkillNameTextBox->SetHeight(mSkillNameHeight);
    mSkillNameTextBox->SetFixedWidth(true);
    mSkillNameTextBox->SetFixedHeight(true);

    mSkillDescriptionTextBox->SetWidth(overlayWidth);
    mSkillDescriptionTextBox->SetHeight(mSkillDescriptionHeight);
    mSkillDescriptionTextBox->SetFixedWidth(true);
    mSkillDescriptionTextBox->SetFixedHeight(true);

    // Center each text box object.
    double horizontalCenter = overlayWidth / 2.0;
    double skillNameYPos = ((double)mSkillNameHeight / 2.0) + mSkillDescriptionHeight;
    double skillDescriptionYPos = (double)mSkillDescriptionHeight / 2.0;
    mSkillNameTextBox->GetParent()->SetPosition(glm::vec3(horizontalCenter,
                                                          skillNameYPos,
                                                          0.0));
    mSkillDescriptionTextBox->GetParent()->SetPosition(glm::vec3(horizontalCenter,
                                                                 skillDescriptionYPos,
                                                                 0.0));
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionAdded()
{
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionHovered()
{
  auto action = GetCurrentlyHoveredAction();
  if(action != nullptr &&
     mSkillNameTextBox != nullptr &&
     mSkillDescriptionTextBox != nullptr)
  {
    mSkillNameTextBox->SetText(action->GetName());
    mSkillDescriptionTextBox->SetText(action->GetDescription());

    // If the action is disabled, change the text color.
    auto skillTextShader = mSkillNameTextBox->GetTextShader();
    auto descriptionTextShader = mSkillDescriptionTextBox->GetTextShader();
    if(!action->IsEnabled())
    {
      if(skillTextShader != nullptr)
      {
        skillTextShader->Activate();
        skillTextShader->SetVec4("textColor", (glm::vec4(DARK_COLOR, 1.0)));
      }

      if(descriptionTextShader != nullptr)
      {
        descriptionTextShader->Activate();
        descriptionTextShader->SetVec4("textColor", (glm::vec4(DARK_COLOR, 1.0)));
      }
    }
    else
    {
      if(skillTextShader != nullptr)
      {
        skillTextShader->Activate();
        skillTextShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
      }

      if(descriptionTextShader != nullptr)
      {
        descriptionTextShader->Activate();
        descriptionTextShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
      }
    }
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionExecuted()
{
  // When a skill is executed, this menu is no longer needed.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->ScheduleForDeletion();
  }
}
