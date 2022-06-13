#include "SkillMenuLayoutComponent.hpp"

#include <algorithm>

#include <Environment.hpp>
#include <GameObject.hpp>
#include <SpriteComponent.hpp>

#include "Colors.hpp"
#include "Fonts.hpp"

using Barebones::SkillMenuLayoutComponent;

/******************************************************************************/
SkillMenuLayoutComponent::SkillMenuLayoutComponent()
  : MenuLayoutComponent()
  , mSkillNameTextBox(nullptr)
  , mSkillDescriptionTextBox(nullptr)
  , mLeftCursor(nullptr)
  , mRightCursor(nullptr)
  , mSkillNameHeight(100)
  , mSkillNameVerticalPadding(25)
  , mSkillDescriptionHeight(45)
  , mSkillDescriptionVerticalPadding(15)
{
  SetWraparoundEnabled(false);
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
    mSkillNameTextBox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    mSkillNameTextBox->SetTextSize(BIGGEST_FONT_SIZE);
    mSkillNameTextBox->SetTextAlignment(TextAlignment::eCENTER);
    mSkillNameTextBox->SetVerticalPadding(mSkillNameVerticalPadding);

    auto skillTextShader = mSkillNameTextBox->GetTextShader();
    if(skillTextShader != nullptr)
    {
      skillTextShader->Activate();
      skillTextShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    }

    mSkillDescriptionTextBox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    mSkillDescriptionTextBox->SetTextSize(MEDIUM_FONT_SIZE);
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

    // Create two cursors and their sprites.
    auto leftCursorObject = std::make_unique<UrsineEngine::GameObject>("leftCursor");
    auto leftCursorSprite = std::make_unique<UrsineEngine::SpriteComponent>();
    leftCursorObject->SetScale(glm::vec3(5.0, 5.0, 1.0));
    leftCursorObject->SetRotation(180, glm::vec3(0.0, 1.0, 0.0));
    leftCursorSprite->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    auto rightCursorObject = std::make_unique<UrsineEngine::GameObject>("rightCursor");
    auto rightCursorSprite = std::make_unique<UrsineEngine::SpriteComponent>();
    rightCursorObject->SetScale(glm::vec3(5.0, 5.0, 1.0));
    rightCursorSprite->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    UrsineEngine::Texture cursorTexture;
    cursorTexture.SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    cursorTexture.SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    cursorTexture.CreateTextureFromFile("resources/sprites/gui/menuArrow.png");
    leftCursorSprite->SetTexture(cursorTexture);
    rightCursorSprite->SetTexture(cursorTexture);

    std::string vertexFile = "resources/shaders/TexturedMeshWithFadeShader.vert";
    std::string fragmentFile = "resources/shaders/TexturedMeshWithFadeShader.frag";

    leftCursorSprite->AddShader("default", UrsineEngine::Shader(vertexFile, fragmentFile));
    leftCursorSprite->SetCurrentShader("default");
    rightCursorSprite->AddShader("default", UrsineEngine::Shader(vertexFile, fragmentFile));
    rightCursorSprite->SetCurrentShader("default");

    leftCursorObject->AddComponent(std::move(leftCursorSprite));
    rightCursorObject->AddComponent(std::move(rightCursorSprite));
    parent->AddChild(std::move(leftCursorObject));
    mLeftCursor = parent->GetChildren().back();
    parent->AddChild(std::move(rightCursorObject));
    mRightCursor = parent->GetChildren().back();
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionAdded()
{
  UpdateCursors();
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

    // Update the cursors.
    UpdateCursors();
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::HandleActionExecuted()
{
  // When an action is executed from this menu, this menu is no longer needed.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->ScheduleForDeletion();
  }
}

/******************************************************************************/
void SkillMenuLayoutComponent::UpdateCursors()
{
  auto action = GetCurrentlyHoveredAction();
  if(action != nullptr &&
     mSkillNameTextBox != nullptr &&
     mSkillDescriptionTextBox != nullptr)
  {
    // Move the cursors to either side of the new text.
    if(mLeftCursor != nullptr)
    {
      auto textBoxParent = mSkillNameTextBox->GetParent();
      if(textBoxParent != nullptr)
      {
        auto cursorPos = textBoxParent->GetPosition();
        auto textWidth = mSkillNameTextBox->GetTextWidth();
        cursorPos.x -= (textWidth / 2.0);

        auto cursorMesh = mLeftCursor->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
        if(cursorMesh != nullptr)
        {
          auto cursorScalar = mLeftCursor->GetScalarTransform()[0][0];
          cursorPos.x -= (cursorMesh->GetWidth() * cursorScalar);
        }

        mLeftCursor->SetPosition(cursorPos);
      }

      // Change the cursor color, if necessary.
      auto cursorMesh = mLeftCursor->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
      if(cursorMesh != nullptr)
      {
        auto cursorShader = cursorMesh->GetCurrentShader();
        if(cursorShader != nullptr)
        {
          cursorShader->Activate();

          auto actionName = action->GetName();
          auto actions = GetActions();
          auto findAction = [actionName](const MenuAction* aAction)
          {
            return aAction->GetName() == actionName;
          };

          auto foundAction = std::find_if(actions.begin(),
                                          actions.end(),
                                          findAction);
          if(foundAction == actions.begin())
          {
            cursorShader->SetVec4("fadeColor", glm::vec4(DARK_COLOR, 1.0));
            cursorShader->SetFloat("fadeValue", 1.0);
          }
          else
          {
            cursorShader->SetFloat("fadeValue", 0.0);
          }
        }
      }
    }

    if(mRightCursor != nullptr)
    {
      auto textBoxParent = mSkillNameTextBox->GetParent();
      if(textBoxParent != nullptr)
      {
        auto cursorPos = textBoxParent->GetPosition();
        auto textWidth = mSkillNameTextBox->GetTextWidth();
        cursorPos.x += (textWidth / 2.0);

        auto cursorMesh = mLeftCursor->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
        if(cursorMesh != nullptr)
        {
          auto cursorScalar = mRightCursor->GetScalarTransform()[0][0];
          cursorPos.x += (cursorMesh->GetWidth() * cursorScalar);
        }

        mRightCursor->SetPosition(cursorPos);
      }

      // Change the cursor color, if necessary.
      auto cursorMesh = mRightCursor->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
      if(cursorMesh != nullptr)
      {
        auto cursorShader = cursorMesh->GetCurrentShader();
        if(cursorShader != nullptr)
        {
          cursorShader->Activate();

          auto actionName = action->GetName();
          auto actions = GetActions();
          auto findAction = [actionName](const MenuAction* aAction)
          {
            return aAction->GetName() == actionName;
          };

          auto foundAction = std::find_if(actions.begin(),
                                          actions.end(),
                                          findAction);
          if(foundAction == std::prev(actions.end()))
          {
            cursorShader->SetVec4("fadeColor", glm::vec4(DARK_COLOR, 1.0));
            cursorShader->SetFloat("fadeValue", 1.0);
          }
          else
          {
            cursorShader->SetFloat("fadeValue", 0.0);
          }
        }
      }
    }
  }
}
