#ifndef TURNDISPLAYCOMPONENT_HPP
#define TURNDISPLAYCOMPONENT_HPP

#include <Component.hpp>

#include "TextBoxComponent.hpp"

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
       *
       * @param aTime The start time of the current Scene's Update().
       */
      void Update(double aTime) override;

      /**
       * Displays a "turn began" message for the given player.
       *
       * @param aPlayer The player whose turn began.
       */
      void DisplayMessageForPlayer(UrsineEngine::GameObject& aPlayer);

    private:
      TextBoxComponent* mTextBox;

      double mTextBoxVerticalPadding;

      double mSpeed;
      bool mMoving;

      double mTimeBecamePaused;
      double mTimeToSpendPaused;
      bool mHasPaused;
      bool mCurrentlyPaused;
  };
}

#endif
