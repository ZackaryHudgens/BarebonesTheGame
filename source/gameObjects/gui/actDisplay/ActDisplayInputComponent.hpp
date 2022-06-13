#ifndef ACTDISPLAYINPUTCOMPONENT_HPP
#define ACTDISPLAYINPUTCOMPONENT_HPP

#include "InputComponent.hpp"

namespace Barebones
{
  class ActDisplayInputComponent : public InputComponent
  {
    public:

      /**
       * Constructor.
       */
      ActDisplayInputComponent();

      /**
       * A handler function that gets called whenever the user presses
       * a key.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       */
      void HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                            int aMods) override;

    private:

      /**
       * A handler function that gets called whenever an act display
       * is ready to receive input. If the act display in question is
       * the parent of this component, this component becomes enabled.
       *
       * @param aDisplay The act display that is ready for input.
       */
      void HandleActDisplayReadyForInput(UrsineEngine::GameObject& aDisplay);

      bool mEnabled;
  };
}

#endif
