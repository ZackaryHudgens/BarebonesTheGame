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

    auto textObject = std::make_unique<UrsineEngine::GameObject>("textObject");
    textObject->AddComponent(std::move(textComponent));
    textObject->SetPosition(glm::vec3(0.0, 0.0, 0.1));
    parent->AddChild(std::move(textObject));

    mText = parent->GetChildren().back()->GetFirstComponentOfType<UrsineEngine::TextComponent>();

    // Create a SpriteComponent and a GameObject to hold it.
    auto backgroundSpriteComponent = std::make_unique<UrsineEngine::SpriteComponent>();
    backgroundSpriteComponent->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);
    backgroundSpriteComponent->SetHasTransparency(false);

    std::string vertexFile = "resources/shaders/UIShader.vert";
    std::string fragmentFile = "resources/shaders/UIShader.frag";
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
    mText->SetColor(aColor);
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
          auto textWidth = mText->GetWidth();
          textWidth += mHorizontalPadding;

          auto largerWidth = std::max(backgroundWidth, textWidth);
          auto smallerWidth = std::min(backgroundWidth, textWidth);
          xScalar = smallerWidth == 0 ? 1.0 : (largerWidth / smallerWidth);

          // Update the width value for use with text positioning.
          mWidth = backgroundWidth * xScalar;
        }
        else
        {
          xScalar = (double)mWidth / (double)backgroundWidth;
        }

        // Determine the vertical scalar for the background object. This
        // is done in the same way as the horizontal scalar above.
        double yScalar = 0.0;
        if(!mFixedHeight)
        {
          auto textHeight = mText->GetHeight();
          textHeight += mVerticalPadding;

          auto largerHeight = std::max(backgroundHeight, textHeight);
          auto smallerHeight = std::min(backgroundHeight, textHeight);
          auto yScalar = smallerHeight == 0 ? 1.0 : (largerHeight / smallerHeight);

          // Update the height value for use with text positioning.
          mHeight = backgroundHeight * yScalar;
        }
        else
        {
          yScalar = (double)mHeight / (double)backgroundHeight;
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
