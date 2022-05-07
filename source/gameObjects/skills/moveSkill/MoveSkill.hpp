#ifndef MOVESKILL_HPP
#define MOVESKILL_HPP

#include "Skill.hpp"

namespace Barebones
{
  class MoveSkill : public Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The GameObject that owns this skill.
       */
      MoveSkill(UrsineEngine::GameObject& aParent);

      /**
       * Returns a vector of valid tile locations for executing this skill.
       *
       * @param aBoard A GameObject containing a BoardLayoutComponent.
       */
      TileList GetValidTiles(UrsineEngine::GameObject& aBoard) override;

      /**
       * Sets the number of times this skill can be used until becoming disabled.
       *
       * @param aUses The number of times this skill can be used.
       */
      void SetUsesRemaining(int aUses);

    protected:

      /**
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                            const TileLocation& aLocation) override;

      int mUsesRemaining;
  };
}

#endif
