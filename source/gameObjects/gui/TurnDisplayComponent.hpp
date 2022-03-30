#ifndef TURNDISPLAYCOMPONENT_HPP
#define TURNDISPLAYCOMPONENT_HPP

#include <Component.hpp>
#include <TextComponent.hpp>

namespace Barebones
{
  class TurnDisplayComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      TurnDisplayComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       */
      void Update() override;

      /**
       * Displays a "turn began" message for the given player.
       *
       * @param aPlayer The player whose turn began.
       */
      void DisplayMessageForPlayer(UrsineEngine::GameObject& aPlayer);

    private:
      UrsineEngine::TextComponent* mNameText;

      double mDisplayTime;
      double mInitialDisplayTime;

      bool mDisplaying;
  };
}

#endif
