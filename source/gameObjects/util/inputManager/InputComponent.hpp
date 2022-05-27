#ifndef INPUTCOMPONENT_HPP
#define INPUTCOMPONENT_HPP

#include <Component.hpp>
#include <CoreSignals.hpp>

namespace Barebones
{
  class InputComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      InputComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * A virtual function that gets called whenever the user presses
       * a key.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       */
      virtual void HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                    int aMods) {}

      /**
       * A virtual function that gets called whenever the user holds
       * a key down long enough to repeat the input.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      virtual void HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                     int aMods) {}

    protected:

      /**
       * A virtual function that gets called in Initialize(). Should
       * be overridden if there is any functionality needed by inheriting
       * classes.
       */
      virtual void ProtectedInitialize() {}
  };
}

#endif
