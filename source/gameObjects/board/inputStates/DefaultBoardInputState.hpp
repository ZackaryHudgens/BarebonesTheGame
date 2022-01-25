#ifndef DEFAULTBOARDINPUTSTATE_HPP
#define DEFAULTBOARDINPUTSTATE_HPP

#include "BoardInputState.hpp"

namespace Barebones
{
  class DefaultBoardInputState : public BoardInputState
  {
    public:

      /**
       * Constructor.
       *
       * @param aObject The parent GameObject with a BoardInputComponent.
       */
      DefaultBoardInputState(UrsineEngine::GameObject& aObject);

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
                                                        int aMods) override;

    private:

      /**
       * Sets the hovered property of the tile at the given location
       * (if it exists) to true and un-hovers the tile at the
       * current location.
       *
       * @param aXPos The x position of the new location.
       * @param aYPos The y position of the new location.
       */
      void HoverOverTile(int aXPos,
                         int aYPos);
  };
}

#endif
