#ifndef BOARDINPUTSTATE_HPP
#define BOARDINPUTSTATE_HPP

#include <CoreSignals.hpp>
#include <GameObject.hpp>

namespace Barebones
{
  class BoardInputState
  {
    public:

      /**
       * Constructor.
       *
       * @param aObject The parent GameObject with a BoardInputComponent.
       * @param aXPos The initial x position of the player.
       * @paray aYPos The initial y position of the player.
       */
      BoardInputState(UrsineEngine::GameObject& aObject,
                      int aXPos = 0,
                      int aYPos = 0);

      /**
       * A handler function that gets called whenever the user presses
       * a key.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      std::unique_ptr<BoardInputState> HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
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
      std::unique_ptr<BoardInputState> HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                         int aMods);

      /**
       * Returns the player's x location.
       *
       * @return The player's x location.
       */
      int GetPlayerXLocation() const { return mPlayerXLocation; }

      /**
       * Returns the player's y location.
       *
       * @return The player's y location.
       */
      int GetPlayerYLocation() const { return mPlayerYLocation; }

    protected:

      /**
       * Returns the parent GameObject.
       *
       * @return The parent GameObject.
       */
      UrsineEngine::GameObject* GetParent() { return mParent; }

      /**
       * A virtual function that gets called whenever the user presses
       * a key.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      virtual std::unique_ptr<BoardInputState> ProtectedHandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                         int aMods);

      /**
       * A virtual function that gets called whenever the user holds
       * a key down long enough to repeat the input.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      virtual std::unique_ptr<BoardInputState> ProtectedHandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                          int aMods);

      /**
       * Sets the player's x location.
       *
       * @param aXPos The player's x location.
       */
      void SetPlayerXLocation(int aXPos) { mPlayerXLocation = aXPos; }

      /**
       * Sets the player's y location.
       *
       * @param aXPos The player's y location.
       */
      void SetPlayerYLocation(int aYPos) { mPlayerYLocation = aYPos; }

    private:
      UrsineEngine::GameObject* mParent;

      int mPlayerXLocation;
      int mPlayerYLocation;
  };
}

#endif
