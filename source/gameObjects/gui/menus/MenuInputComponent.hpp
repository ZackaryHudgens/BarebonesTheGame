#ifndef MENUINPUTCOMPONENT_HPP
#define MENUINPUTCOMPONENT_HPP

#include <Component.hpp>
#include <CoreSignals.hpp>

namespace Barebones
{
  class MenuInputComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      MenuInputComponent();

      /**
       * Sets whether this component should process input.
       *
       * @param aEnabled Whether to process input.
       */
      void SetEnabled(bool aEnabled) { mEnabled = aEnabled; }

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

      bool mEnabled;
  };
}

#endif
