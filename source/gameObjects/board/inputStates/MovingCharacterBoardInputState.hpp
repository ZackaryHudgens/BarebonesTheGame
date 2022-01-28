#ifndef MOVINGCHARACTERBOARDINPUTSTATE_HPP
#define MOVINGCHARACTERBOARDINPUTSTATE_HPP

#include "BoardInputState.hpp"

namespace Barebones
{
  class MovingCharacterBoardInputState : public BoardInputState
  {
    public:

      /**
       * Constructor.
       *
       * @param aObject The parent GameObject with a BoardInputComponent.
       * @param aXPos The initial x position of the player.
       * @param aYPos The initial y position of the player.
       */
      MovingCharacterBoardInputState(UrsineEngine::GameObject& aObject,
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
                                                        int aMods) override;

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
