#ifndef BOARDUSINGSKILLSTATE_HPP
#define BOARDUSINGSKILLSTATE_HPP

#include "BoardState.hpp"

#include <Observer.hpp>

namespace Barebones
{
  class BoardUsingSkillState : public BoardState
  {
    public:

      /**
       * Constructor.
       *
       * @param aBoard The board this state represents.
       * @param aSkill The skill being used.
       */
      BoardUsingSkillState(UrsineEngine::GameObject& aBoard,
                           Skill& aSkill);

      /**
       * Gets called whenever the board enters this state.
       */
      void OnEnter() override;

      /**
       * Gets called whenever the board exits this state.
       */
      void OnExit() override;

      /**
       * A handler function that gets called whenever a skill is executed
       * on the board.
       *
       * @param aSkill The skill that was executed.
       * @return A pointer to a new state, if necessary.
       */
      std::unique_ptr<BoardState> HandleSkillExecuted(Skill& aSkill) override;

      /**
       * A virtual function that gets called whenever a skill is cancelled.
       *
       * @param aSkill The skill that was cancelled.
       * @return A pointer to a new state, if necessary.
       */
      std::unique_ptr<BoardState> HandleSkillCancelled(Skill& aSkill) override;

    private:

      /**
       * A handler function that gets called whenever a board changes
       * its currently focused tile.
       *
       * @param aBoard The board that changed.
       */
      void HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard);

      /**
       * Un-highlights all pertinent tiles.
       */
      void RemoveHighlights();

      /**
       * Highlights all pertinent tiles.
       */
      void HighlightTiles();

      UrsineEngine::Observer mObserver;

      Skill* mSkill;
      std::vector<UrsineEngine::GameObject*> mHighlightedTiles;
      UrsineEngine::GameObject* mFocusedTile;

      double mHighlightIntensity;
  };
}

#endif
