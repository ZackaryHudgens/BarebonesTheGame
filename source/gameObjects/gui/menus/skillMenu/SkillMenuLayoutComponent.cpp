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
  , mSkillNameBackground(nullptr)
  , mSkillDescriptionBackgroun(nullptr)
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

    // Create the name text and a GameObject to hold it.
    auto skillName = std::make_unique<UrsineEngine::TextComponent>();
    skillName->SetFont("Alagard", "Medium");
    skillName->SetSize(48);
    skillName->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto nameObject = std::make_unique<UrsineEngine::GameObject>("skillName");
    nameObject->AddComponent(std::move(skillName));
    nameObject->SetPosition(glm::vec3(0.0, 100.0, 0.0));
    parent->AddChild(std::move(nameObject));
    mSkillNameText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();

    // Create the description text and a GameObject to hold it.
    auto skillDescription = std::make_unique<UrsineEngine::TextComponent>();
    skillDescription->SetFont("Alagard", "Medium");
    skillDescription->SetSize(32);
    skillDescription->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto descriptionObject = std::make_unique<UrsineEngine::GameObject>("skillDescription");
    descriptionObject->AddComponent(std::move(skillDescription));
    descriptionObject->SetPosition(glm::vec3(0.0, 0.0, 0.0));
    parent->AddChild(std::move(descriptionObject));
    mSkillDescriptionText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();

    // Create a background sprite for the skill name and a GameObject to hold it.
    auto skillNameBackground = std::make_unique<UrsineEngine::SpriteComponent>();
    skillNameBackground->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
    skillNameBackground->SetHasTransparency(false);

    std::string vertexFile = "resources/shaders/UIShader.vert";
    std::string fragmentFile = "resources/shaders/UIShader.frag";
    UrsineEngine::Shader uiShader(vertexFile, fragmentFile);
    skillNameBackground->AddShader("uiShader", uiShader);
    skillNameBackground->SetCurrentShader("uiShader");

    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/menuBox.png");
    skillNameBackground->SetTexture(backgroundTexture);

    // Scale the background to stretch across the overlay.
    double textureWidth = backgroundTexture.GetData().mWidth;
    double textureHeight = backgroundTexture.GetData().mHeight;
    double xScalar = overlayWidth / textureWidth;
    double yScalar = 10.0;

    auto menuBackgroundObject = std::make_unique<UrsineEngine::GameObject>("menuBackground");
    menuBackgroundObject->AddComponent(std::move(menuBackground));
    menuBackgroundObject->SetScale(glm::vec3(xScalar,
                                             yScalar,
                                             1.0));

    double backgroundWidth = xScalar * textureWidth;
    double backgroundHeight = yScalar * textureHeight;
    menuBackgroundObject->SetPosition(glm::vec3(backgroundWidth / 2.0,
                                                overlayHeight - (backgroundHeight / 2.0),
                                                -0.9));
    parent->AddChild(std::move(menuBackgroundObject));
    mBackground = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::SpriteComponent>();
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
