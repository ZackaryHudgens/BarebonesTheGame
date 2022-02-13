#include "SkillMenuLayoutComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>
#include <MeshComponent.hpp>

#include <iostream>

#include "SkillActionBehaviorComponent.hpp"

using Barebones::SkillMenuLayoutComponent;

/******************************************************************************/
SkillMenuLayoutComponent::SkillMenuLayoutComponent()
  : MenuLayoutComponent()
  , mSkillNameText(nullptr)
  , mSkillDescriptionText(nullptr)
  , mIconSpacing(20.0)
{
}

/******************************************************************************/
void SkillMenuLayoutComponent::Initialize()
{
  // Create and add text components to child GameObjects.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Add the name text.
    auto skillName = std::make_unique<UrsineEngine::TextComponent>();
    skillName->SetFont("Alagard", "Medium");
    skillName->SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
    skillName->SetSize(48);
    skillName->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto nameObject = std::make_unique<UrsineEngine::GameObject>("skillName");
    nameObject->AddComponent(std::move(skillName));
    parent->AddChild(std::move(nameObject));
    mSkillNameText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();
    mSkillNameText->GetParent()->SetPosition(glm::vec3(0.0,
                                                       (env.GetGraphicsOptions().mOverlayHeight / 2.0) - 150.0,
                                                       0.0));

    // Add the description text.
    auto skillDescription = std::make_unique<UrsineEngine::TextComponent>();
    skillDescription->SetFont("Alagard", "Medium");
    skillDescription->SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
    skillDescription->SetSize(32);
    skillDescription->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto descriptionObject = std::make_unique<UrsineEngine::GameObject>("skillDescription");
    descriptionObject->AddComponent(std::move(skillDescription));
    parent->AddChild(std::move(descriptionObject));
    mSkillDescriptionText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();
    mSkillDescriptionText->GetParent()->SetPosition(glm::vec3(0.0,
                                                              (env.GetGraphicsOptions().mOverlayHeight / 2.0) - 170.0,
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
  // When an action gets added to the menu, center the skill icons
  // horizontally and vertically.
  double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
  double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;
  double iconXPos = 0.0;
  double iconYPos = overlayHeight / 2.0;

  // First, calculate the total width of all actions and padding.
  double totalWidth = 0;
  for(auto& action : GetActions())
  {
    auto actionMesh = action->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(actionMesh != nullptr)
    {
      // Calculate the width taking any scalar transforms into account.
      auto xScalar = action->GetScalarTransform()[0][0];
      totalWidth += (actionMesh->GetWidth() * xScalar);
    }
  }

  // Next, place each icon accordingly.
  iconXPos = (overlayWidth - totalWidth) / 2.0;
  for(auto& action : GetActions())
  {
    action->SetPosition(glm::vec3(iconXPos,
                                  iconYPos,
                                  0.0));

    auto actionMesh = action->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(actionMesh != nullptr)
    {
      auto xScalar = action->GetScalarTransform()[0][0];
      iconXPos += ((actionMesh->GetWidth() * 2) * xScalar);
    }

    iconXPos += mIconSpacing;
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionHovered()
{
  auto action = GetCurrentlyHoveredAction();
  if(action != nullptr)
  {
    auto skillActionComponent = action->GetFirstComponentOfType<SkillActionBehaviorComponent>();
    auto skillIconComponent = action->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(skillActionComponent != nullptr &&
       skillIconComponent != nullptr)
    {
      // Update the text to reflect the hovered skill.
      mSkillNameText->SetText(skillActionComponent->GetSkillName());
      mSkillDescriptionText->SetText(skillActionComponent->GetSkillDescription());

      // Update the text position to be centered horizontally and
      // placed beneath the current icon.
      double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;

      auto iconPos = action->GetPosition();
      auto iconYScalar = action->GetScalarTransform()[1][1];
      double iconHeight = skillIconComponent->GetHeight() * iconYScalar;

      double nameWidth = mSkillNameText->GetWidth();
      double nameHeight = mSkillNameText->GetHeight();
      double descriptionWidth = mSkillDescriptionText->GetWidth();
      double descriptionHeight = mSkillDescriptionText->GetHeight();

      double nameXPos = (overlayWidth - nameWidth) / 2.0;
      double nameYPos = iconPos.y - (iconHeight / 2.0) - nameHeight - (mIconSpacing * 3);
      double descriptionXPos = (overlayWidth - descriptionWidth) / 2.0;
      double descriptionYPos = nameYPos - descriptionHeight - mIconSpacing;

      mSkillNameText->GetParent()->SetPosition(glm::vec3(nameXPos,
                                                         nameYPos,
                                                         0.0));
      mSkillDescriptionText->GetParent()->SetPosition(glm::vec3(descriptionXPos,
                                                                descriptionYPos,
                                                                0.0));
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
