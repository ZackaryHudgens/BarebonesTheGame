#ifndef DEFAULTBOARDINPUTSTATE_HPP
#define DEFAULTBOARDINPUTSTATE_HPP

#include "BoardInputState.hpp"

#include "BoardLayoutComponent.hpp"

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

      /**
       * A handler function that gets called whenever the player's location
       * on the board has changed.
       *
       * @param aPrevLocation The previous location of the player.
       * @param aNewLocation The new location of the player.
       */
      void HandlePlayerMoved(const TileLocation& aPrevLocation,
                             const TileLocation& aNewLocation) override;

    private:

      /**
       * Attempts to move the player's position to the tile at the
       * given location.
       *
       * @param aLocation The location of the tile to move to.
       */
      void MoveToTile(const TileLocation& aLocation);

      /**
       * Creates a skill menu for a given character and adds it to the
       * current scene.
       *
       * @param aObject The character in question.
       */
      void CreateSkillMenu(UrsineEngine::GameObject& aObject);

      glm::vec3 mHighlightColor;
  };
}

#endif
