#include "TextBoxComponent.hpp"

#include <GameObject.hpp>

#include <iostream>

using Barebones::TextBoxComponent;

/******************************************************************************/
TextBoxComponent::TextBoxComponent()
  : Component()
  , mText(nullptr)
  , mBackground(nullptr)
  , mTextAlignment(TextAlignment::eLEFT)
  , mWidth(0)
  , mHeight(0)
  , mFixedWidth(false)
  , mFixedHeight(false)
  , mHorizontalPadding(0)
  , mVerticalPadding(0)
{
}

/******************************************************************************/
void TextBoxComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    // Create a TextComponent and a GameObject to hold it.
    auto textComponent = std::make_unique<UrsineEngine::TextComponent>();
    textComponent->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

    std::string vertexFile = "resources/shaders/TextShader.vert";
    std::string fragmentFile = "resources/shaders/TextShader.frag";
    UrsineEngine::Shader textShader(vertexFile, fragmentFile);
    textComponent->AddShader("textShader", textShader);
    textComponent->SetCurrentShader("textShader");

    auto textObject = std::make_unique<UrsineEngine::GameObject>("textObject");
    textObject->AddComponent(std::move(textComponent));
    textObject->SetPosition(glm::vec3(0.0, 0.0, 0.1));
    parent->AddChild(std::move(textObject));

    mText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();

    // Create a SpriteComponent and a GameObject to hold it.
    auto backgroundSpriteComponent = std::make_unique<UrsineEngine::SpriteComponent>();
    backgroundSpriteComponent->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
    backgroundSpriteComponent->SetHasTransparency(false);

    vertexFile = "resources/shaders/TexturedMeshShader.vert";
    fragmentFile = "resources/shaders/TexturedMeshShader.frag";
    UrsineEngine::Shader backgroundShader(vertexFile, fragmentFile);
    backgroundSpriteComponent->AddShader("backgroundShader", backgroundShader);
    backgroundSpriteComponent->SetCurrentShader("backgroundShader");

    auto backgroundSpriteObject = std::make_unique<UrsineEngine::GameObject>("backgroundSpriteObject");
    backgroundSpriteObject->AddComponent(std::move(backgroundSpriteComponent));
    backgroundSpriteObject->SetPosition(glm::vec3(0.0, 0.0, -0.1));
    parent->AddChild(std::move(backgroundSpriteObject));

    mBackground = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::SpriteComponent>();
  }
}

/******************************************************************************/
void TextBoxComponent::SetText(const std::string& aText)
{
  if(mText != nullptr)
  {
    mText->SetText(aText);

    ResizeBackground();
    RepositionText();
  }
}

/******************************************************************************/
std::string TextBoxComponent::GetText() const
{
  std::string text;

  if(mText != nullptr)
  {
    text = mText->GetText();
  }

  return text;
}

/******************************************************************************/
bool TextBoxComponent::SetFont(const std::string& aFamily,
                               const std::string& aStyle)
{
  bool success = false;

  if(mText != nullptr)
  {
    success = mText->SetFont(aFamily,
                             aStyle);

    if(success)
    {
      ResizeBackground();
      RepositionText();
    }
  }

  return success;
}

/******************************************************************************/
bool TextBoxComponent::SetTextSize(int aSize)
{
  bool success = false;

  if(mText != nullptr)
  {
    success = mText->SetSize(aSize);

    if(success)
    {
      ResizeBackground();
      RepositionText();
    }
  }

  return success;
}

/******************************************************************************/
void TextBoxComponent::SetTextColor(const glm::vec4& aColor)
{
  if(mText != nullptr)
  {
    auto textShader = mText->GetCurrentShader();
    if(textShader != nullptr)
    {
      textShader->Activate();
      textShader->SetVec4("textColor", aColor);
    }
  }
}

/******************************************************************************/
void TextBoxComponent::SetTextAlignment(const TextAlignment& aAlignment)
{
  mTextAlignment = aAlignment;
  RepositionText();
}

/******************************************************************************/
void TextBoxComponent::SetTexture(const UrsineEngine::Texture& aTexture)
{
  if(mBackground != nullptr)
  {
    mBackground->SetTexture(aTexture);
  }
}

/******************************************************************************/
void TextBoxComponent::SetWidth(int aWidth)
{
  mWidth = aWidth;

  RepositionText();
}

/******************************************************************************/
void TextBoxComponent::SetHeight(int aHeight)
{
  mHeight = aHeight;

  RepositionText();
}

/******************************************************************************/
void TextBoxComponent::SetHorizontalPadding(int aPadding)
{
  mHorizontalPadding = aPadding;

  ResizeBackground();
  RepositionText();
}

/******************************************************************************/
void TextBoxComponent::SetVerticalPadding(int aPadding)
{
  mVerticalPadding = aPadding;

  ResizeBackground();
  RepositionText();
}

/******************************************************************************/
void TextBoxComponent::ResizeBackground()
{
  if(mBackground != nullptr &&
     mText != nullptr)
  {
    auto backgroundObject = mBackground->GetParent();
    if(backgroundObject != nullptr)
    {
      auto backgroundWidth = mBackground->GetWidth();
      auto backgroundHeight = mBackground->GetHeight();

      // If the background has no width and/or height, there is no
      // resizing to be done.
      if(backgroundWidth > 0.0 &&
         backgroundHeight > 0.0)
      {
        // Determine the horizontal scalar for the background object. If
        // the width is not fixed, the scalar is calculated to make the object
        // just large enough to fit the text and the horizontal padding.
        // If it is fixed, the scalar is calculated to make the background
        // object the width of the set value.
        double xScalar = 0.0;
        if(!mFixedWidth)
        {
          double textWidth = mText->GetWidth();
          xScalar = (textWidth + mHorizontalPadding) / (std::max(backgroundWidth, 1.0));

          // Update the width value for use with text positioning.
          mWidth = backgroundWidth * xScalar;
        }
        else
        {
          xScalar = (double)mWidth / (std::max((double)backgroundWidth, 1.0));
        }

        // Determine the vertical scalar for the background object. This
        // is done in the same way as the horizontal scalar above.
        double yScalar = 0.0;
        if(!mFixedHeight)
        {
          double textHeight = mText->GetHeight();
          yScalar = (textHeight + mVerticalPadding) / (std::max(backgroundHeight, 1.0));

          // Update the height value for use with text positioning.
          mHeight = backgroundHeight * yScalar;
        }
        else
        {
          yScalar = (double)mHeight / (std::max((double)backgroundHeight, 1.0));
        }

        // Scale the background object.
        backgroundObject->SetScale(glm::vec3(xScalar,
                                             yScalar,
                                             1.0));
      }
    }
  }
}

/******************************************************************************/
void TextBoxComponent::RepositionText()
{
  auto parent = GetParent();
  if(mText != nullptr &&
     parent != nullptr)
  {
    auto textObject = mText->GetParent();
    if(textObject != nullptr)
    {
      auto leftEdge = parent->GetPosition().x - ((double)mWidth / 2.0);
      auto bottomEdge = parent->GetPosition().y - ((double)mHeight / 2.0);

      switch(mTextAlignment)
      {
        case TextAlignment::eCENTER:
        {
          auto textWidth = mText->GetWidth();
          auto textPos = textObject->GetPosition();
          textPos.x = leftEdge + ((mWidth - textWidth) / 2.0);
          textPos.y = bottomEdge + mVerticalPadding;
          textObject->SetPosition(textPos);

          break;
        }
        case TextAlignment::eLEFT:
        {
          auto textPos = textObject->GetPosition();
          textPos.x = leftEdge + mHorizontalPadding;
          textPos.y = bottomEdge + mVerticalPadding;
          textObject->SetPosition(textPos);

          break;
        }
        case TextAlignment::eRIGHT:
        {
          break;
        }
        default:
        {
          break;
        }
      }
    }
  }
}
