#ifndef BOARDINPUTCOMPONENT_HPP
#define BOARDINPUTCOMPONENT_HPP

// TODO: To pass control between the board and the GUI, create
// a signal for BoardExitControl and GUIExitControl. On BoardExitControl,
// the GUI activates, and on GUIExitControl, the board activates.
// While one is active, the other has a nullptr for the state.

#include <Component.hpp>
#include <CoreSignals.hpp>

#include "BoardInputState.hpp"

namespace Barebones
{
  class BoardInputComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      BoardInputComponent();

      /**
       * Loads the component.
       */
      void Load() override;

    private:

      /**
       * A handler function that gets called whenever the user presses
       * a key.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       */
      void HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                            int aMods);

      /**
       * A handler function that gets called whenever the user holds
       * a key down long enough to repeat the input.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      void HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                             int aMods);

      std::unique_ptr<BoardInputState> mState;
  };
}

#endif
