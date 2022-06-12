#ifndef SCROLLINGMESSAGEBEHAVIORCOMPONENT_HPP
#define SCROLLINGMESSAGEBEHAVIORCOMPONENT_HPP

#include <Component.hpp>

#include <string>

namespace Barebones
{
  class ScrollingMessageBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       *
       * @param aText The message to display.
       * @param aFontSize The size of the font to use.
       * @param aSpeed The speed at which to scroll.
       */
      ScrollingMessageBehaviorComponent(const std::string& aText,
                                        int aFontSize,
                                        double aSpeed);

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       *
       * @param aTime The start time of the current scene's Update().
       */
      void Update(double aTime) override;

    private:
      std::string mText;
      int mFontSize;
      double mSpeed;

      int mTextBoxVerticalPadding;

      bool mMoving;

      double mTimeBecamePaused;
      double mTimeToSpendPaused;
      bool mHasPaused;
      bool mCurrentlyPaused;
  };
}

#endif
