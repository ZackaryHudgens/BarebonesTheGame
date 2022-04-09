#include "SkillMenuLayoutComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>
#include <SpriteComponent.hpp>

#include "SkillActionBehaviorComponent.hpp"

using Barebones::SkillMenuLayoutComponent;

/******************************************************************************/
SkillMenuLayoutComponent::SkillMenuLayoutComponent()
  : MenuLayoutComponent()
  , mSkillNameTextBox(nullptr)
  , mSkillDescriptionTextBox(nullptr)
{
}

/******************************************************************************/
void SkillMenuLayoutComponent::Initialize()
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
    backgroundTexture.CreateTextureFromFile("resources/sprites/menuBox.png");
    mSkillNameTextBox->SetTexture(backgroundTexture);
    mSkillDescriptionTextBox->SetTexture(backgroundTexture);

    // Set the font parameters for both text boxes.
    mSkillNameTextBox->SetFont("Alagard", "Medium");
    mSkillNameTextBox->SetTextSize(72);
    mSkillNameTextBox->SetTextAlignment(TextAlignment::eLEFT);
    mSkillNameTextBox->SetTextColor(glm::vec4(0.247, 0.314, 0.247, 1.0));

    mSkillDescriptionTextBox->SetFont("Alagard", "Medium");
    mSkillDescriptionTextBox->SetTextSize(48);
    mSkillDescriptionTextBox->SetTextAlignment(TextAlignment::eLEFT);
    mSkillDescriptionTextBox->SetTextColor(glm::vec4(0.247, 0.314, 0.247, 1.0));

    // Center both of the text boxes.
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;
    double horizontalCenter = overlayWidth / 2.0;

    mSkillNameTextBox->GetParent()->SetPosition(glm::vec3(horizontalCenter,
                                                          100.0 / 2.0,
                                                          0.0));
    mSkillDescriptionTextBox->GetParent()->SetPosition(glm::vec3(horizontalCenter,
                                                                 (50.0 / 2.0) + 100.0 + 15.0,
                                                                 0.0));
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::Update()
{
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionAdded()
{
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionHovered()
{
  auto action = GetCurrentlyHoveredAction();
  if(action != nullptr)
  {
    auto skillAction = action->GetFirstComponentOfType<SkillActionBehaviorComponent>();
    if(skillAction != nullptr)
    {
      auto skill = skillAction->GetSkill();
      if(skill != nullptr &&
         mSkillNameTextBox != nullptr &&
         mSkillDescriptionTextBox != nullptr)
      {
        mSkillNameTextBox->SetText(skill->GetName());
        mSkillDescriptionTextBox->SetText(skill->GetDescription());
      }
    }
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionSelected()
{
  // When a skill is selected, this menu is no longer needed.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->ScheduleForDeletion();
  }
}
