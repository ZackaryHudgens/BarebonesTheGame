#ifndef INPUTMANAGERCOMPONENT_HPP
#define INPUTMANAGERCOMPONENT_HPP

#include <stack>

#include <Component.hpp>

#include "InputComponent.hpp"

namespace Barebones
{
  class InputManagerComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      InputManagerComponent();

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

      /**
       * A handler function that gets called whenever a GameObject is
       * about to be deleted.
       *
       * @param aObject The GameObject about to be deleted.
       */
      void HandleObjectPendingDeletion(UrsineEngine::GameObject& aObject);

      std::stack<InputComponent*> mInputStack;
  };
}

#endif
