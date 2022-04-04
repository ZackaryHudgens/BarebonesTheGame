#include "SkillMenuLayoutComponent.hpp"

#include <Environment.hpp>
#include <GameObject.hpp>
#include <SpriteComponent.hpp>

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
  auto parent = GetParent();
  if(parent != nullptr)
  {
    double overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
    double overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

    // Add the name text.
    auto skillName = std::make_unique<UrsineEngine::TextComponent>();
    skillName->SetFont("Alagard", "Medium");
    skillName->SetSize(48);
    skillName->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto nameObject = std::make_unique<UrsineEngine::GameObject>("skillName");
    nameObject->AddComponent(std::move(skillName));
    nameObject->SetPosition(glm::vec3(0.0, 100.0, 0.0));
    parent->AddChild(std::move(nameObject));
    mSkillNameText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();

    // Add the description text.
    auto skillDescription = std::make_unique<UrsineEngine::TextComponent>();
    skillDescription->SetFont("Alagard", "Medium");
    skillDescription->SetSize(32);
    skillDescription->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto descriptionObject = std::make_unique<UrsineEngine::GameObject>("skillDescription");
    descriptionObject->AddComponent(std::move(skillDescription));
    descriptionObject->SetPosition(glm::vec3(0.0, 0.0, 0.0));
    parent->AddChild(std::move(descriptionObject));
    mSkillDescriptionText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();

    // Create a menu background.
    auto menuBackground = std::make_unique<UrsineEngine::SpriteComponent>();
    menuBackground->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/menuBox.png");
    menuBackground->SetTexture(backgroundTexture);

    std::string vertexFile = "resources/shaders/UIShader.vert";
    std::string fragmentFile = "resources/shaders/UIShader.frag";
    UrsineEngine::Shader uiShader(vertexFile, fragmentFile);
    menuBackground->AddShader("uiShader", uiShader);
    menuBackground->SetCurrentShader("uiShader");

    auto menuBackgroundObject = std::make_unique<UrsineEngine::GameObject>("menuBackground");
    menuBackgroundObject->AddComponent(std::move(menuBackground));
    menuBackgroundObject->SetPosition(glm::vec3(0.0, 0.0, -0.9));
    parent->AddChild(std::move(menuBackgroundObject));
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
      if(skill != nullptr)
      {
        mSkillNameText->SetText(skill->GetName());
        mSkillDescriptionText->SetText(skill->GetDescription());
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
