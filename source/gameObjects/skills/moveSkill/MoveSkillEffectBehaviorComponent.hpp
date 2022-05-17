#ifndef MOVESKILLEFFECTBEHAVIORCOMPONENT_HPP
#define MOVESKILLEFFECTBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "TileUtil.hpp"

#include "HumanPlayerBehaviorComponent.hpp"

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
       * Sets the board to use when highlighting tiles.
       *
       * @param aBoard The board to use when highlighting tiles.
       */
      void SetBoard(UrsineEngine::GameObject& aBoard);

      /**
       * Sets the list of shortest paths to use when highlighting
       * tiles.
       *
       * @param aPathList The list of paths to use when highlighting tiles.
       */
      void SetShortestPathList(const TilePathList& aPathList);

    protected:

      /**
       * A handler function that gets called whenever a player's location
       * changes.
       *
       * @param aPlayer The player that moved.
       */
      void HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer);

    private:
      UrsineEngine::GameObject* mBoard;
      MoveSkill* mMoveSkill;

      TilePathList mShortestPaths;
      TileList mHighlightedTiles;
  };
}

#endif
