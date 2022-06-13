#ifndef ACTDISPLAYBEHAVIORCOMPONENT_HPP
#define ACTDISPLAYBEHAVIORCOMPONENT_HPP

#include <Component.hpp>

#include "TextBoxComponent.hpp"

namespace Barebones
{
  class ActDisplayBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      ActDisplayBehaviorComponent();

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

      /**
       * A handler function that gets called whenever the user decides to
       * advance past the act display. If the act display in question is
       * the parent of this component, this component begins fading out.
       *
       * @param aDisplay The display the user is moving past.
       */
      void HandleActDisplayAdvanced(UrsineEngine::GameObject& aDisplay);

      TextBoxComponent* mActNameTextbox;
      TextBoxComponent* mActDescriptionTextbox;

      double mFadeSpeed;
      double mFadeValue;

      bool mFadingIn;
      bool mFadingOut;
  };
}

#endif
