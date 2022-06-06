#ifndef AREAOFEFFECTSKILL_HPP
#define AREAOFEFFECTSKILL_HPP

#include "Skill.hpp"

namespace Barebones
{
  class AreaOfEffectSkill : public Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character GameObject that owns this skill.
       * @param aRadius The radius of this skill.
       */
      AreaOfEffectSkill(UrsineEngine::GameObject& aCharacter, int aRadius);

      /**
       * Returns a vector of valid tile locations for executing this skill.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get valid tiles for.
       */
      TileList GetValidTiles(UrsineEngine::GameObject& aBoard,
                             const TileLocation& aSourceLocation) override;

      /**
       * Returns all tiles affected by this skill.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get affected tiles for.
       */
      TileList GetAffectedTiles(UrsineEngine::GameObject& aBoard,
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
      int mRadius;
  };
}

#endif
