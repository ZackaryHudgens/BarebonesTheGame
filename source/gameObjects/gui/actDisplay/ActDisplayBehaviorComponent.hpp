#ifndef ACTDISPLAYBEHAVIORCOMPONENT_HPP
#define ACTDISPLAYBEHAVIORCOMPONENT_HPP

#include <Component.hpp>

#include "TextBoxComponent.hpp"

#include "Acts.hpp"

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

      /**
       * Changes the text displayed based on the given act.
       *
       * @param aAct The act to display text for.
       */
      void DisplayTextForAct(const Act& aAct);

    private:

      /**
       * A handler function that gets called whenever the user decides to
       * advance past the act display. If the act display in question is
       * the parent of this component, this component begins fading out.
       *
       * @param aDisplay The display the user is moving past.
       */
      void HandleActDisplayAdvanced(UrsineEngine::GameObject& aDisplay);

      /**
       * Updates the text boxes to display the act name and description.
       */
      void UpdateText();

      TextBoxComponent* mActNameTextbox;
      TextBoxComponent* mActDescriptionTextbox;

      std::string mActName;
      std::string mActDescription;

      double mFadeSpeed;
      double mFadeValue;

      bool mFadingIn;
      bool mFadingOut;
  };
}

#endif
