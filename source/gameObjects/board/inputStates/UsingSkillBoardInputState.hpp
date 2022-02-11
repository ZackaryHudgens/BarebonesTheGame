#ifndef USINGSKILLBOARDINPUTSTATE_HPP
#define USINGSKILLBOARDINPUTSTATE_HPP

#include "BoardInputState.hpp"

namespace Barebones
{
  class UsingSkillBoardInputState : public BoardInputState
  {
    public:

      /**
       * Constructor.
       *
       * @param aObject The parent GameObject with a BoardInputComponent.
       * @param aSkill A GameObject with a CharacterSkillComponent.
       * @param aXPos The initial x position of the player.
       * @param aYPos The initial y position of the player.
       */
      UsingSkillBoardInputState(UrsineEngine::GameObject& aObject,
                                UrsineEngine::GameObject& aSkill);

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
       * @return A pointer to a new state if this movement caused the input
       *         to move to a new state, otherwise nullptr.
       */
      std::unique_ptr<BoardInputState> HandlePlayerMoved(const TileLocation& aPrevLocation,
                                                         const TileLocation& aNewLocation) override;

    private:
      UrsineEngine::GameObject* mSkill;

      std::vector<UrsineEngine::GameObject*> mHighlightedTiles;
  };
}

#endif
