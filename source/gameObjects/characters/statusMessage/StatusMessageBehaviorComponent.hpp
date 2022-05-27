#ifndef STATUSMESSAGEBEHAVIORCOMPONENT_HPP
#define STATUSMESSAGEBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <TextComponent.hpp>

namespace Barebones
{
  class StatusMessageBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      StatusMessageBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       *
       * @param aTime The start time of the current Scene's Update().
       */
      void Update(double aTime) override;

      /**
       * Sets the text to display.
       *
       * @param aText The text to display.
       */
      void SetText(const std::string& aText);

      /**
       * Returns the TextComponent this status message is using.
       *
       * @return A const pointer to the TextComponent.
       */
      const UrsineEngine::TextComponent* GetTextComponent() const { return mTextComponent; }

    private:
      UrsineEngine::TextComponent* mTextComponent;

      std::string mText;
  };
}

#endif
