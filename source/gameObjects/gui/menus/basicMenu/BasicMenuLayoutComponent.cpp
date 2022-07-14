#include "BasicMenuLayoutComponent.hpp"

#include <algorithm>

#include <Environment.hpp>
#include <GameObject.hpp>
#include <SpriteComponent.hpp>

#include "Colors.hpp"
#include "Fonts.hpp"

using Barebones::BasicMenuLayoutComponent;

/******************************************************************************/
BasicMenuLayoutComponent::BasicMenuLayoutComponent()
  : MenuLayoutComponent()
  , mCursor(nullptr)
  , mHoveredTextBox(nullptr)
  , mVerticalPadding(20)
  , mHorizontalPadding(15)
  , mTextboxHeight(70)
  , mTextBoxWidth(500)
  , mCursorHorizontalPadding(75)
{
}

/******************************************************************************/
void BasicMenuLayoutComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a cursor.
    auto cursorObject = std::make_unique<UrsineEngine::GameObject>("cursor");
    auto cursorSprite = std::make_unique<UrsineEngine::SpriteComponent>();
    cursorSprite->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    UrsineEngine::Texture spriteTexture;
    spriteTexture.SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    spriteTexture.SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    spriteTexture.CreateTextureFromFile("resources/sprites/gui/menuArrow.png");
    cursorSprite->SetTexture(spriteTexture);

    std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
    std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
    UrsineEngine::Shader spriteShader(vertexFile, fragmentFile);
    cursorSprite->AddShader("default", spriteShader);
    cursorSprite->SetCurrentShader("default");

    cursorObject->AddComponent(std::move(cursorSprite));
    cursorObject->SetScale(glm::vec3(5.0, 5.0, 1.0));
    parent->AddChild(std::move(cursorObject));
    mCursor = parent->GetChildren().back();
  }
}

/******************************************************************************/
void BasicMenuLayoutComponent::HandleActionAdded(MenuAction& aAction)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a new GameObject with a TextBoxComponent, then add it as a child.
    auto actionObject = std::make_unique<UrsineEngine::GameObject>(aAction.GetName());
    actionObject->AddComponent(std::make_unique<TextBoxComponent>());
    parent->AddChild(std::move(actionObject));

    auto newActionTextBox = parent->GetChildren().back()->GetFirstComponentOfType<TextBoxComponent>();

    // Set the text box dimensions.
    newActionTextBox->SetHorizontalPadding(mVerticalPadding);
    newActionTextBox->SetVerticalPadding(mVerticalPadding);
    newActionTextBox->SetHeight(mTextboxHeight);
    newActionTextBox->SetWidth(mTextBoxWidth);
    newActionTextBox->SetFixedHeight(true);
    newActionTextBox->SetFixedWidth(true);

    // Set a background texture for this text box.
    UrsineEngine::Texture backgroundTexture;
    backgroundTexture.CreateTextureFromFile("resources/sprites/gui/menuBox.png");
    newActionTextBox->SetTexture(backgroundTexture);

    // Set the font parameters for this text box.
    newActionTextBox->SetFont(DEFAULT_FONT_FAMILY, DEFAULT_FONT_STYLE);
    newActionTextBox->SetTextSize(BIG_FONT_SIZE);
    newActionTextBox->SetTextAlignment(TextAlignment::eCENTER);
    newActionTextBox->SetText(aAction.GetName());

    auto textShader = newActionTextBox->GetTextShader();
    if(textShader != nullptr)
    {
      textShader->Activate();
      textShader->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    }

    mTextBoxes.emplace_back(newActionTextBox);
    RepositionTextBoxes();
    RepositionCursor(aAction);
  }
}

/******************************************************************************/
void BasicMenuLayoutComponent::HandleActionHovered(MenuAction& aAction)
{
  RepositionCursor(aAction);
}

/******************************************************************************/
void BasicMenuLayoutComponent::HandleActionEnabledChanged(MenuAction& aAction)
{
  // Find the text box that corresponds to the action.
  auto actionName = aAction.GetName();

  auto findTextBox = [&actionName](const TextBoxComponent* aTextBox)
  {
    return actionName == aTextBox->GetText();
  };

  auto foundTextBox = std::find_if(mTextBoxes.begin(),
                                   mTextBoxes.end(),
                                   findTextBox);
  if(foundTextBox != mTextBoxes.end())
  {
    // Change the text color based on whether the action was enabled
    // or disabled.
    if(aAction.IsEnabled())
    {
      (*foundTextBox)->GetTextShader()->SetVec4("textColor", glm::vec4(BACKGROUND_COLOR, 1.0));
    }
    else
    {
      (*foundTextBox)->GetTextShader()->SetVec4("textColor", glm::vec4(DARK_COLOR, 1.0));
    }
  }
}

/******************************************************************************/
void BasicMenuLayoutComponent::RepositionTextBoxes()
{
  auto overlayWidth = env.GetGraphicsOptions().mOverlayWidth;
  auto overlayHeight = env.GetGraphicsOptions().mOverlayHeight;

  auto totalTextBoxHeight = (mTextboxHeight + mVerticalPadding) * mTextBoxes.size();
  auto distanceFromTop = overlayHeight - ((overlayHeight - totalTextBoxHeight) / 2.0);

  for(auto& textBox : mTextBoxes)
  {
    auto textBoxParent = textBox->GetParent();
    if(textBoxParent != nullptr)
    {
      auto textBoxPos = textBoxParent->GetPosition();
      textBoxPos.x = (overlayWidth / 2.0);
      textBoxPos.y = distanceFromTop;
      textBoxParent->SetPosition(textBoxPos);

      distanceFromTop -= (mTextboxHeight + mVerticalPadding);
    }
  }
}

/******************************************************************************/
void BasicMenuLayoutComponent::RepositionCursor(MenuAction& aAction)
{
  // Find the text box that corresponds to the action.
  auto actionName = aAction.GetName();

  auto findTextBox = [&actionName](const TextBoxComponent* aTextBox)
  {
    return actionName == aTextBox->GetText();
  };

  auto foundTextBox = std::find_if(mTextBoxes.begin(),
                                   mTextBoxes.end(),
                                   findTextBox);
  if(foundTextBox != mTextBoxes.end())
  {
    // Move the cursor to the left of the text in the text box.
    auto textBoxParent = (*foundTextBox)->GetParent();
    if(textBoxParent != nullptr &&
       mCursor != nullptr)
    {
      auto cursorPos = textBoxParent->GetPosition();

      double leftEdge = cursorPos.x - ((*foundTextBox)->GetWidth() / 2.0);
      cursorPos.x = (leftEdge + mCursorHorizontalPadding);
      mCursor->SetPosition(cursorPos);
    }
  }
}
