#ifndef TEXTBOXCOMPONENT_HPP
#define TEXTBOXCOMPONENT_HPP

#include <Component.hpp>
#include <SpriteComponent.hpp>
#include <TextComponent.hpp>

namespace Barebones
{
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
       * Sets the text to display.
       *
       * @param aText The text to display.
       */
      void SetText(const std::string& aText);

      /**
       * Returns the currently displayed text.
       *
       * @return The currently displayed text.
       */
      std::string GetText() const;

      /**
       * Sets the width of the text box (in pixels).
       *
       * @param aWidth The width of the text box (in pixels).
       */
      void SetWidth(int aWidth);

      /**
       * Sets the height of the text box (in pixels).
       *
       * @param aHeight The height of the text box (in pixels).
       */
      void SetHeight(int aHeight);

    private:
      UrsineEngine::SpriteComponent* mBackground;
      UrsineEngine::TextComponent* mText;
  };
}

#endif
