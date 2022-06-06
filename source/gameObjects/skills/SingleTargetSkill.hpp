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
       *
       * @param aCharacter The character GameObject that owns this skill.
       * @param aRange The range of this skill.
       */
      SingleTargetSkill(UrsineEngine::GameObject& aCharacter, int aRange);

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
