#ifndef TEXTBOXCOMPONENT_HPP
#define TEXTBOXCOMPONENT_HPP

#include <Component.hpp>
#include <SpriteComponent.hpp>
#include <TextComponent.hpp>
#include <Texture.hpp>

namespace Barebones
{
  enum class TextAlignment
  {
    eLEFT,
    eRIGHT,
    eCENTER
  };

  class TextBoxComponent : public UrsineEngine::Component
  {
    public:

      /**
      * Constructor.
      */
      TextBoxComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Sets the text to display. The background mesh will be resized
       * to fit the new text (unless the width and height are fixed).
       *
       * @param aText The text to display.
       */
      void SetText(const std::string& aText);

      /**
       * Returns the text on display.
       *
       * @return The text on display.
       */
      std::string GetText() const;

      /**
       * Sets the font for the text. If no font with the given family/style
       * combination has been loaded, this function fails.
       *
       * @param aFamily The family name of the font.
       * @param aStyle The style of the font.
       * @return True if successful, false otherwise.
       */
      bool SetFont(const std::string& aFamily,
                   const std::string& aStyle);

      /**
       * Sets the size (height) of the text (in pixels). This may fail;
       * if it does, the size will not change.
       *
       * @param aSize The new size (height) for the text (in pixels).
       * @return True if successful, false otherwise.
       */
      bool SetTextSize(int aSize);

      /**
       * Sets the color of the text.
       *
       * @param aColor The new color of the text.
       */
      void SetTextColor(const glm::vec4& aColor);

      /**
       * Sets the alignment of the text. Text is aligned with regard to
       * the background mesh.
       *
       * @param aAlignment The new alignment of the text.
       */
      void SetTextAlignment(const TextAlignment& aAlignment);

      /**
       * Sets the texture to use for the background.
       *
       * @param aTexture The new background texture.
       */
      void SetTexture(const UrsineEngine::Texture& aTexture);

      /**
       * Sets the width (in pixels) of the background mesh. Note that
       * unless the width is fixed, this may change to fit text.
       *
       * @param aWidth The new width (in pixels) of the background mesh.
       */
      void SetWidth(int aWidth);

      /**
       * Returns the width of this text box.
       *
       * @return The width of this text box.
       */
      int GetWidth() const { return mWidth; }

      /**
       * Sets the height (in pixels) of the background mesh. Note that
       * unless the height is fixed, this may change to fit text.
       *
       * @param aHeight The new height (in pixels) of the background mesh.
       */
      void SetHeight(int aHeight);

      /**
       * Returns the height of this text box.
       *
       * @return The height of this text box.
       */
      int GetHeight() const { return mHeight; }

      /**
       * Returns the width of the text only.
       *
       * @return The width of the text only.
       */
      int GetTextWidth() const;

      /**
       * Returns the height of the text only.
       *
       * @return The height of the text only.
       */
      int GetTextHeight() const;

      /**
       * Sets the fixed width property of this text box. If the width is
       * fixed, then it won't be changed when resizing to fit text.
       *
       * @param aFixed Whether to fix the width of this text box.
       */
      void SetFixedWidth(bool aFixed) { mFixedWidth = aFixed; }

      /**
       * Sets the fixed height property of this text box. If the height is
       * fixed, then it won't be changed when resizing to fit text.
       *
       * @param aFixed Whether to fix the height of this text box.
       */
      void SetFixedHeight(bool aFixed) { mFixedHeight = aFixed; }

      /**
       * Sets the horizontal padding (in pixels) for this text box.
       *
       * @param aPadding The horizontal padding (in pixels) for this text box.
       */
      void SetHorizontalPadding(int aPadding);

      /**
       * Sets the vertical padding (in pixels) for this text box.
       *
       * @param aPadding The certical padding (in pixels) for this text box.
       */
      void SetVerticalPadding(int aPadding);

    private:

      /**
       * Resizes the background sprite to fit the current text.
       */
      void ResizeBackground();

      /**
       * Repositions the text according to the text alignment.
       */
      void RepositionText();

      UrsineEngine::TextComponent* mText;
      UrsineEngine::SpriteComponent* mBackground;

      TextAlignment mTextAlignment;

      int mWidth;
      int mHeight;
      bool mFixedWidth;
      bool mFixedHeight;

      int mHorizontalPadding;
      int mVerticalPadding;
  };
}

#endif
