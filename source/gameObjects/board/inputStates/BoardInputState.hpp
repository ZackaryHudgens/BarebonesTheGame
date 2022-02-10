#ifndef BOARDINPUTSTATE_HPP
#define BOARDINPUTSTATE_HPP

#include <CoreSignals.hpp>
#include <GameObject.hpp>

#include "BoardLayoutComponent.hpp"

namespace Barebones
{
  class BoardInputState
  {
    public:

      /**
       * Constructor.
       *
       * @param aObject The parent GameObject with a BoardInputComponent.
       */
      BoardInputState(UrsineEngine::GameObject& aObject);

      /**
       * A virtual function that gets called whenever the user presses
       * a key. Should be overridden by inheriting state classes.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      virtual std::unique_ptr<BoardInputState> HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                int aMods) { return nullptr; }

      /**
       * A virtual function that gets called whenever the user holds
       * a key down long enough to repeat the input. Should be overridden
       * by inheriting state classes.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      virtual std::unique_ptr<BoardInputState> HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                 int aMods) { return nullptr; }

      /**
       * A virtual function that gets called whenever the player's location
       * on the board has changed.
       *
       * @param aPrevLocation The previous location of the player.
       * @param aNewLocation The new location of the player.
       */
      virtual void HandlePlayerMoved(const TileLocation& aPrevLocation,
                                     const TileLocation& aNewLocation) {}

    protected:

      /**
       * Returns the parent GameObject.
       *
       * @return The parent GameObject.
       */
      UrsineEngine::GameObject* GetParent() { return mParent; }

    private:
      UrsineEngine::GameObject* mParent;
  };
}

#endif
