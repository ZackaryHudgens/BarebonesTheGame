#ifndef SINGLETARGETSKILL_HPP
#define SINGLETARGETSKILL_HPP

#include "Skill.hpp"

namespace Barebones
{
  class SingleTargetSkill : public Skill
  {
    public:

      /**
       * Constructor.
       */
      SingleTargetSkill();

      /**
       * Returns a vector of valid tile locations for executing this skill.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get valid tiles for.
       */
      TileList GetValidTiles(UrsineEngine::GameObject& aBoard,
                             const TileLocation& aSourceLocation) override;

      /**
       * Returns a vector of tiles to highlight.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get highlighted tiles for.
       */
      TileList GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                   const TileLocation& aSourceLocation) override;

      /**
       * Sets the range of this skill.
       *
       * @param aRange The new range of this skill.
       */
      void SetRange(int aRange) { mRange = aRange; }

      /**
       * Returns the range of this skill.
       *
       * @return The range of this skill.
       */
      int GetRange() const { return mRange; }

    private:
      int mRange;
  };
}

#endif
