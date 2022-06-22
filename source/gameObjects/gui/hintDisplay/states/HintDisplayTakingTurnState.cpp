#include "HintDisplayTakingTurnState.hpp"

#include <Environment.hpp>
#include <SpriteComponent.hpp>

#include "TextBoxComponent.hpp"

#include "Colors.hpp"
#include "Fonts.hpp"
#include "Signals.hpp"

using Barebones::HintDisplayTakingTurnState;

/******************************************************************************/
HintDisplayTakingTurnState::HintDisplayTakingTurnState(UrsineEngine::GameObject& aParent)
  : HintDisplayState(aParent)
  , mEndTurnText(nullptr)
  , mElementPadding(15)
  , mIconScale(5.0)
{
  SkillSelected.Connect(mObserver, [this](Skill& aSkill)
  {
    this->HandleSkillSelected(aSkill);
  });

  SkillExecuted.Connect(mObserver, [this](Skill& aSkill)
  {
    this->HandleSkillExecuted(aSkill);
  });

  SkillCancelled.Connect(mObserver, [this](Skill& aSkill)
  {
    this->HandleSkillCancelled(aSkill);
  });
}

/******************************************************************************/
void HintDisplayTakingTurnState::OnEnter()
{
  CreatePauseIconAndText();
  CreateSelectIconAndText();
  CreateEndTurnIconAndText();
  CreateZoomIconAndText();
}

/******************************************************************************/
void HintDisplayTakingTurnState::OnExit()
{
  for(auto& element : mElements)
  {
    element->ScheduleForDeletion();
  }

  mEndTurnText = nullptr;
}

/******************************************************************************/
void HintDisplayTakingTurnState::CreatePauseIconAndText()
{
  // Create the pause icon.
  auto pauseIconObject = CreateIconObject("pauseIcon",
                                          "resources/sprites/gui/keycapEsc.png");
  auto pauseIcon = pauseIconObject->GetFirstComponentOfType<UrsineEngine::MeshComponent>();

  // Create the pause text.
  auto pauseTextObject = CreateTextObject("pauseText",
                                          "PAUSE");

  // Place the icon and text on the screen, then add them as child GameObjects.
  int halfIconHeight = pauseIcon->GetHeight() / 2.0;
  int halfIconWidth = pauseIcon->GetWidth() / 2.0;
  int yPos = mElementPadding + (halfIconHeight * mIconScale);
  int xPos = mElementPadding + (halfIconWidth * mIconScale);
  pauseIconObject->SetPosition(glm::vec3(xPos, yPos, 0.9));

  yPos += (halfIconHeight * mIconScale);
  pauseTextObject->SetPosition(glm::vec3(xPos, yPos, 0.9));

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
void HintDisplayTakingTurnState::CreateSelectIconAndText()
{
  // Create the select icon.
  auto selectIconObject = CreateIconObject("selectIcon",
                                           "resources/sprites/gui/keycapEnter.png");
  auto selectIcon = selectIconObject->GetFirstComponentOfType<UrsineEngine::MeshComponent>();

  // Create the select text.
  auto selectTextObject = CreateTextObject("selectText",
                                           "SELECT");

  // Place the icon and text on the screen, then add them as child GameObjects.
  int halfIconHeight = selectIcon->GetHeight() / 2.0;
  int halfIconWidth = selectIcon->GetWidth() / 2.0;
  int yPos = mElementPadding + (halfIconHeight * mIconScale);
  int xPos = mElementPadding + (halfIconWidth * mIconScale) + 150;
  selectIconObject->SetPosition(glm::vec3(xPos, yPos, 0.9));

  yPos += (halfIconHeight * mIconScale);
  selectTextObject->SetPosition(glm::vec3(xPos, yPos, 0.9));

  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->AddChild(std::move(selectIconObject));
    mElements.emplace_back(parent->GetChildren().back());

    parent->AddChild(std::move(selectTextObject));
    mElements.emplace_back(parent->GetChildren().back());
  }
}

/******************************************************************************/
void HintDisplayTakingTurnState::CreateEndTurnIconAndText()
{
  // Create the end turn icon.
  auto endTurnIconObject = CreateIconObject("endTurnIcon",
                                            "resources/sprites/gui/keycapQ.png");
  auto endTurnIcon = endTurnIconObject->GetFirstComponentOfType<UrsineEngine::MeshComponent>();

  // Create the end turn text.
  auto endTurnTextObject = CreateTextObject("endTurnText",
                                            "END TURN");

  // Place the icon and text on the screen, then add them as child GameObjects.
  int halfIconHeight = endTurnIcon->GetHeight() / 2.0;
  int halfIconWidth = endTurnIcon->GetWidth() / 2.0;
  int yPos = mElementPadding + (halfIconHeight * mIconScale);
  int xPos = mElementPadding + (halfIconWidth * mIconScale) + 375;
  endTurnIconObject->SetPosition(glm::vec3(xPos, yPos, 0.9));

  yPos += (halfIconHeight * mIconScale);
  endTurnTextObject->SetPosition(glm::vec3(xPos, yPos, 0.9));

  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->AddChild(std::move(endTurnIconObject));
    mElements.emplace_back(parent->GetChildren().back());

    parent->AddChild(std::move(endTurnTextObject));
    mElements.emplace_back(parent->GetChildren().back());

    mEndTurnText = mElements.back()->GetFirstComponentOfType<TextBoxComponent>();
  }
}

/******************************************************************************/
void HintDisplayTakingTurnState::CreateZoomIconAndText()
{
  // Create the zoom icon.
  auto zoomIconObject = CreateIconObject("zoomIcon",
                                         "resources/sprites/gui/keycapZ.png");
  auto zoomIcon = zoomIconObject->GetFirstComponentOfType<UrsineEngine::MeshComponent>();

  // Create the zoom text.
  auto zoomTextObject = CreateTextObject("zoomText",
                                         "ZOOM");
  auto zoomText = zoomTextObject->GetFirstComponentOfType<TextBoxComponent>();

  // Place the icon and text on the screen, then add them as child GameObjects.
  int halfIconHeight = zoomIcon->GetHeight() / 2.0;
  int halfIconWidth = zoomIcon->GetWidth() / 2.0;

  auto overlayWidth = env.GetGraphicsOptions().mOverlayWidth;

  int yPos = mElementPadding + (halfIconHeight * mIconScale);
  int xPos = overlayWidth - (mElementPadding + (halfIconWidth * mIconScale));
  zoomIconObject->SetPosition(glm::vec3(xPos, yPos, 0.9));

  yPos += (halfIconHeight * mIconScale);
  zoomTextObject->SetPosition(glm::vec3(xPos, yPos, 0.9));

  auto parent = GetParent();
  if(parent != nullptr)
  {
    parent->AddChild(std::move(zoomIconObject));
    mElements.emplace_back(parent->GetChildren().back());

    parent->AddChild(std::move(zoomTextObject));
    mElements.emplace_back(parent->GetChildren().back());
  }
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> HintDisplayTakingTurnState::CreateIconObject(const std::string& aName,
                                                                                    const std::string& aFile)
{
  auto newObject = std::make_unique<UrsineEngine::GameObject>(aName);
  newObject->SetScale(glm::vec3(mIconScale, mIconScale, 1.0));

  auto newIcon = std::make_unique<UrsineEngine::SpriteComponent>();
  newIcon->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

  UrsineEngine::Texture texture;
  texture.CreateTextureFromFile(aFile);
  newIcon->SetTexture(texture);

  std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
  std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
  UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);
  newIcon->AddShader("default", defaultShader);
  newIcon->SetCurrentShader("default");

  newObject->AddComponent(std::move(newIcon));

  return std::move(newObject);
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> HintDisplayTakingTurnState::CreateTextObject(const std::string& aName,
                                                                                    const std::string& aText)
{
  auto newObject = std::make_unique<UrsineEngine::GameObject>(aName);
  newObject->AddComponent(std::make_unique<TextBoxComponent>());
  auto newText = newObject->GetFirstComponentOfType<TextBoxComponent>();

  newText->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
  newText->SetTextSize(MEDIUM_FONT_SIZE);
  newText->SetTextAlignment(TextAlignment::eCENTER);
  newText->SetText(aText);

  std::string vertexFile = "resources/shaders/OutlinedTextShader.vert";
  std::string fragmentFile = "resources/shaders/OutlinedTextShader.frag";
  UrsineEngine::Shader outlineShader(vertexFile, fragmentFile);
  outlineShader.Activate();
  outlineShader.SetVec4("textColor", glm::vec4(FOREGROUND_COLOR, 1.0));
  outlineShader.SetVec4("outlineColor", glm::vec4(BACKGROUND_COLOR, 1.0));
  outlineShader.SetFloat("outlineWidth", 2.0);
  newText->SetTextShader(outlineShader);

  return std::move(newObject);
}

/******************************************************************************/
void HintDisplayTakingTurnState::HandleSkillSelected(Skill& aSkill)
{
  if(mEndTurnText != nullptr)
  {
    mEndTurnText->SetText("CANCEL");
  }
}

/******************************************************************************/
void HintDisplayTakingTurnState::HandleSkillExecuted(Skill& aSkill)
{
  if(mEndTurnText != nullptr)
  {
    mEndTurnText->SetText("END TURN");
  }
}

/******************************************************************************/
void HintDisplayTakingTurnState::HandleSkillCancelled(Skill& aSkill)
{
  HandleSkillExecuted(aSkill);
}
