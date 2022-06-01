#ifndef SIMPLESKILL_HPP
#define SIMPLESKILL_HPP

#include "Skill.hpp"

namespace Barebones
{
  class SimpleSkill : public Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The GameObject that owns this skill.
       * @param aRange The range of this skill.
       */
      SimpleSkill(UrsineEngine::GameObject& aParent, int aRange);

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

    private:
      int mRange;
  };
}

#endif
