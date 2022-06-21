#include "HintDisplayDefaultState.hpp"

#include <SpriteComponent.hpp>

#include "TextBoxComponent.hpp"

#include "Colors.hpp"
#include "Fonts.hpp"

using Barebones::HintDisplayDefaultState;

/******************************************************************************/
HintDisplayDefaultState::HintDisplayDefaultState(UrsineEngine::GameObject& aParent)
  : HintDisplayState(aParent)
  , mCameraIcon(nullptr)
  , mVerticalPadding(25)
{
}

/******************************************************************************/
void HintDisplayDefaultState::OnEnter()
{
  CreatePauseIconAndText();
  CreateMovementIconsAndText();
  CreateSelectIconAndText();
  CreateCameraIcons();
}

/******************************************************************************/
void HintDisplayDefaultState::OnExit()
{
  for(auto& element : mElements)
  {
    element->ScheduleForDeletion();
  }
}

/******************************************************************************/
void HintDisplayDefaultState::CreatePauseIconAndText()
{
  // Create the pause icon.
  auto pauseIconObject = std::make_unique<UrsineEngine::GameObject>("pauseIcon");
  pauseIconObject->SetScale(glm::vec3(5.0, 5.0, 1.0));
  auto pauseIcon = std::make_unique<UrsineEngine::SpriteComponent>();
  pauseIcon->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

  UrsineEngine::Texture pauseTexture;
  pauseTexture.CreateTextureFromFile("resources/sprites/gui/keycapEsc.png");
  pauseIcon->SetTexture(pauseTexture);

  std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
  std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
  UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);
  pauseIcon->AddShader("default", defaultShader);
  pauseIcon->SetCurrentShader("default");

  // Create the pause text.
  auto pauseTextObject = std::make_unique<UrsineEngine::GameObject>("pauseText");
  pauseTextObject->AddComponent(std::make_unique<TextBoxComponent>());
  auto pauseText = pauseTextObject->GetFirstComponentOfType<TextBoxComponent>();

  pauseText->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
  pauseText->SetTextSize(MEDIUM_FONT_SIZE);
  pauseText->SetTextAlignment(TextAlignment::eLEFT);
  pauseText->SetText("PAUSE");

  vertexFile = "resources/shaders/OutlinedTextShader.vert";
  fragmentFile = "resources/shaders/OutlinedTextShader.frag";
  UrsineEngine::Shader outlineShader(vertexFile, fragmentFile);
  outlineShader.Activate();
  outlineShader.SetVec4("textColor", glm::vec4(FOREGROUND_COLOR, 1.0));
  outlineShader.SetVec4("outlineColor", glm::vec4(BACKGROUND_COLOR, 1.0));
  outlineShader.SetFloat("outlineWidth", 2.0);
  pauseText->SetTextShader(outlineShader);

  // Place the icon and text on the foreground and add them to the scene.
  int xPos = mVerticalPadding;
  pauseIconObject->SetPosition(glm::vec3(xPos, mVerticalPadding, 0.9));

  xPos += pauseIcon->GetWidth();
  pauseTextObject->SetPosition(glm::vec3(xPos, mVerticalPadding, 0.9));

  pauseIconObject->AddComponent(std::move(pauseIcon));

  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->AddChild(std::move(pauseIconObject));
    mElements.emplace_back(parent->GetChildren().back());

    parent->AddChild(std::move(pauseTextObject));
    mElements.emplace_back(parent->GetChildren().back());
  }
}

/******************************************************************************/
void HintDisplayDefaultState::CreateMovementIconsAndText()
{
}

/******************************************************************************/
void HintDisplayDefaultState::CreateSelectIconAndText()
{
}

/******************************************************************************/
void HintDisplayDefaultState::CreateCameraIcons()
{
}
