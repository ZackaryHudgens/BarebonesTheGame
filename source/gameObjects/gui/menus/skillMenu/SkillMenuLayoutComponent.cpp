#include "SkillMenuLayoutComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>
#include <MeshComponent.hpp>

#include "SkillActionBehaviorComponent.hpp"

#include <iostream>

using Barebones::SkillMenuLayoutComponent;

/******************************************************************************/
SkillMenuLayoutComponent::SkillMenuLayoutComponent()
  : MenuLayoutComponent()
  , mSkillNameText(nullptr)
  , mSkillDescriptionText(nullptr)
  , mIconSpacing(100.0)
  , mTargetPosition(0.0, 0.0, 0.0)
  , mSpeed(0.3)
  , mMoving(false)
{
}

/******************************************************************************/
void SkillMenuLayoutComponent::Initialize()
{
  double targetHeight = (double)env.GetGraphicsOptions().mOverlayHeight / 2.0;
  mTargetPosition = glm::vec3(0.0,
                              targetHeight,
                              0.0);
  mMoving = true;

  // Create and add text components to child GameObjects.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto skillName = std::make_unique<UrsineEngine::TextComponent>();
    skillName->SetFont("Roboto", "Regular");
    skillName->SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
    skillName->SetSize(32);
    skillName->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto nameObject = std::make_unique<UrsineEngine::GameObject>("skillName");
    nameObject->AddComponent(std::move(skillName));
    parent->AddChild(std::move(nameObject));
    mSkillNameText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();

    auto skillDescription = std::make_unique<UrsineEngine::TextComponent>();
    skillDescription->SetFont("Roboto", "Regular");
    skillDescription->SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
    skillDescription->SetSize(24);
    skillDescription->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto descriptionObject = std::make_unique<UrsineEngine::GameObject>("skillDescription");
    descriptionObject->AddComponent(std::move(skillDescription));
    parent->AddChild(std::move(descriptionObject));
    mSkillDescriptionText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::Update()
{
  if(mMoving)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      auto position = glm::mix(parent->GetPosition(),
                               mTargetPosition,
                               mSpeed);

      // If the position is close enough to the target position,
      // move directly to the target position and stop moving.
      if(std::abs(mTargetPosition.x - position.x) <= 0.005 &&
         std::abs(mTargetPosition.y - position.y) <= 0.005 &&
         std::abs(mTargetPosition.z - position.z) <= 0.005)
      {
        parent->SetPosition(mTargetPosition);
        mMoving = false;
      }
      else
      {
        parent->SetPosition(position);
      }
    }
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionAdded()
{
  auto actions = GetActions();
  double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
  int xPadding = 50;

  // First, calculate the total width of all actions and padding.
  double totalWidth = 0;
  for(auto& action : actions)
  {
    auto actionMesh = action->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(actionMesh != nullptr)
    {
      // Calculate the width taking any scalar transforms into account.
      auto xScalar = action->GetScalarTransform()[0][0];
      totalWidth += (actionMesh->GetWidth() * xScalar);
      totalWidth += xPadding;
    }
  }

  // Next, place each icon accordingly.
  double distanceFromLeft = (overlayWidth - totalWidth) / 2.0;
  int numIcons = 0;
  for(auto& action : actions)
  {
    auto actionMesh = action->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
    if(actionMesh != nullptr)
    {
      // The origin of the icon is in the center, so calculate how far
      // the left edge of the icon is from the origin.
      auto xScalar = action->GetScalarTransform()[0][0];
      double halfWidth = (actionMesh->GetWidth() * xScalar) / 2.0;

      double xPos = distanceFromLeft + halfWidth + (numIcons * xPadding);
      action->SetPosition(glm::vec3(xPos,
                                    0.0,
                                    0.0));
      ++numIcons;
    }
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionHovered()
{
  auto action = GetCurrentlyHoveredAction();
  if(action != nullptr)
  {
    auto skillActionComponent = action->GetFirstComponentOfType<SkillActionBehaviorComponent>();
    if(skillActionComponent != nullptr)
    {
      mSkillNameText->SetText(skillActionComponent->GetSkillName());
      mSkillDescriptionText->SetText(skillActionComponent->GetSkillDescription());

      // Align the text objects.
      double middle = (double)env.GetGraphicsOptions().mOverlayWidth / 2.0;
      double nameXPosition = middle - (double)mSkillNameText->GetWidth() / 2.0;
      double nameYPosition = (double)mSkillDescriptionText->GetHeight() - 135;
      double descriptionXPosition = middle - (double)mSkillDescriptionText->GetWidth() / 2.0;

      mSkillNameText->GetParent()->SetPosition(glm::vec3(nameXPosition,
                                                         nameYPosition,
                                                         0.0));
      mSkillDescriptionText->GetParent()->SetPosition(glm::vec3(descriptionXPosition,
                                                                -150.0,
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
