#include "TextBoxComponent.hpp"

#include <GameObject.hpp>

using Barebones::TextBoxComponent;

/******************************************************************************/
TextBoxComponent::TextBoxComponent()
  : Component()
  , mText(nullptr)
  , mBackground(nullptr)
  , mTextAlignment(TextAlignment::eLEFT)
  , mHorizontalPadding(150)
  , mVerticalPadding(50)
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
      double zScalar = scalarTransform[3][3];

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
          // Determine the x-position.
          double backgroundLeftMargin = backgroundObject->GetPosition().x - (mBackground->GetWidth() / 2.0);
          double xPos = backgroundLeftMargin + mHorizontalPadding;

          // Determine the y-position.
          double backgroundHeight = mBackground->GetHeight();
          double yPos = backgroundHeight - mVerticalPadding;

          auto textPos = textObject->GetPosition();
          textPos.x = xPos;
          textPos.y = yPos;
          textObject->SetPosition(textPos);
          break;
        }
        case TextAlignment::eRIGHT:
        {
          break;
        }
        case TextAlignment::eCENTER:
        {
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
