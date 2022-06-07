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
       */
      AreaOfEffectSkill();

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

      /**
       * Sets the radius of this skill.
       *
       * @param aRadius The new radius of this skill.
       */
      void SetRadius(int aRadius) { mRadius = aRadius; }

      /**
       * Returns the radius of this skill.
       *
       * @return The radius of this skill.
       */
      int GetRadius() const { return mRadius; }

    private:
      int mRadius;
  };
}

#endif
