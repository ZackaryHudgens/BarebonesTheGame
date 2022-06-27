#ifndef MOVESKILLEFFECTBEHAVIORCOMPONENT_HPP
#define MOVESKILLEFFECTBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "TileUtil.hpp"

namespace Barebones
{
  class MoveSkill;

  class MoveSkillEffectBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       *
       * @param aSkill The MoveSkill to highlight tiles for.
       */
      MoveSkillEffectBehaviorComponent(MoveSkill& aSkill);

      /**
       * Sets the board to highlight tiles on.
       *
       * @param aBoard The board to use when highlighting tiles.
       */
      void SetBoard(UrsineEngine::GameObject& aBoard) { mBoard = &aBoard; }

      /**
       * Sets the list of shortest paths to use when highlighting
       * tiles.
       *
       * @param aPathList The list of paths to use when highlighting tiles.
       */
      void SetShortestPathList(const TilePathList& aPathList) { mShortestPaths = aPathList; }

      /**
       * Sets the starting location to use when highlighting tiles.
       *
       * @param aLocation The starting location to use when highlighting tiles.
       */
      void SetStartingLocation(const TileLocation& aLocation) { mStartingLocation = aLocation; }

    protected:

      /**
       * A handler function that gets called whenever a board's focused
       * tile changes.
       *
       * @param aBoard The board that updated.
       */
      void HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard);

    private:
      UrsineEngine::GameObject* mBoard;
      MoveSkill* mMoveSkill;

      TilePathList mShortestPaths;
      TileList mHighlightedTiles;
      TileLocation mStartingLocation;
  };
}

#endif
