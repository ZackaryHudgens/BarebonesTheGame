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
  , mHorizontalPadding(50)
  , mVerticalPadding(5)
  , mFixedWidth(false)
  , mFixedHeight(false)
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
  if(!mFixedWidth)
  {
    if(mBackground != nullptr)
    {
      auto backgroundObject = mBackground->GetParent();
      if(backgroundObject != nullptr)
      {
        double currentWidth = mBackground->GetWidth();
        double scalar = (double)aWidth / currentWidth;

        auto scalarTransform = backgroundObject->GetScalarTransform();
        backgroundObject->SetScale(glm::vec3(scalar,
                                             scalarTransform[1][1],
                                             scalarTransform[2][2]));

        RepositionText();
      }
    }
  }
}

/******************************************************************************/
void TextBoxComponent::SetHeight(int aHeight)
{
  if(!mFixedHeight)
  {
    if(mBackground != nullptr)
    {
      auto backgroundObject = mBackground->GetParent();
      if(backgroundObject != nullptr)
      {
        double currentHeight = mBackground->GetHeight();
        double scalar = (double)aHeight / currentHeight;

        auto scalarTransform = backgroundObject->GetScalarTransform();
        backgroundObject->SetScale(glm::vec3(scalarTransform[0][0],
                                             scalar,
                                             scalarTransform[2][2]));

        RepositionText();
      }
    }
  }
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
  if(mText != nullptr &&
     mBackground != nullptr)
  {
    auto textObject = mText->GetParent();
    auto backgroundObject = mBackground->GetParent();
    if(textObject != nullptr &&
       backgroundObject != nullptr)
    {
      // Use the dimensions of the text and the padding values to determine
      // how large the background needs to be to fit the text.
      double textWidth = mText->GetWidth();
      double textHeight = mText->GetHeight();

      // Only update the width and height if they aren't fixed.
      double backgroundWidth = mBackground->GetWidth();
      double backgroundHeight = mBackground->GetHeight();
      double newBackgroundWidth = textWidth + (mHorizontalPadding * 2);
      double newBackgroundHeight = textHeight + (mVerticalPadding * 2);

      auto scalarTransform = backgroundObject->GetScalarTransform();
      double xScalar = mFixedWidth ? scalarTransform[0][0] : newBackgroundWidth / backgroundWidth;
      double yScalar = mFixedHeight ? scalarTransform[1][1] : newBackgroundHeight / backgroundHeight;
      double zScalar = scalarTransform[2][2];

      backgroundObject->SetScale(glm::vec3(xScalar,
                                           yScalar,
                                           zScalar));
    }
  }
}

/******************************************************************************/
void TextBoxComponent::RepositionText()
{
  if(mBackground != nullptr &&
     mText != nullptr)
  {
    auto backgroundObject = mBackground->GetParent();
    auto textObject = mText->GetParent();
    if(textObject != nullptr &&
       backgroundObject != nullptr)
    {
      switch(mTextAlignment)
      {
        case TextAlignment::eLEFT:
        {
          auto backgroundScaleTransform = backgroundObject->GetScalarTransform();
          double backgroundWidth = mBackground->GetWidth() * backgroundScaleTransform[0][0];
          double backgroundHeight = mBackground->GetHeight() * backgroundScaleTransform[1][1];
          double backgroundLeftEdge = backgroundObject->GetPosition().x - (backgroundWidth / 2.0);
          double backgroundBottomEdge = backgroundObject->GetPosition().y - (backgroundHeight / 2.0);

          auto textPos = textObject->GetPosition();
          textPos.x = backgroundLeftEdge + mHorizontalPadding;
          textPos.y = backgroundBottomEdge + mVerticalPadding;
          textObject->SetPosition(textPos);

          break;
        }
        case TextAlignment::eRIGHT:
        {
          break;
        }
        case TextAlignment::eCENTER:
        {
          auto backgroundScaleTransform = backgroundObject->GetScalarTransform();
          double backgroundWidth = mBackground->GetWidth() * backgroundScaleTransform[0][0];
          double backgroundHeight = mBackground->GetHeight() * backgroundScaleTransform[1][1];
          double backgroundBottomEdge = backgroundObject->GetPosition().y - (backgroundHeight / 2.0);

          auto textWidth = mText->GetWidth();
          auto textHeight = mText->GetHeight();
          auto distanceFromLeft = (backgroundWidth - textWidth) / 2.0;

          auto textPos = textObject->GetPosition();
          textPos.x = distanceFromLeft;
          textPos.y = backgroundBottomEdge + mVerticalPadding;
          textObject->SetPosition(textPos);

          break;
        }
        default:
        {
          break;
        }
      };
    }
  }
}
