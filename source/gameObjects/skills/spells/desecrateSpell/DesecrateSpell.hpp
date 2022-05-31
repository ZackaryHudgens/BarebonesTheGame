#ifndef DESECRATESPELL_HPP
#define DESECRATESPELL_HPP

#include "Skill.hpp"

namespace Barebones
{
  class DesecrateSpell : public Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The GameObject that owns this skill.
       */
      DesecrateSpell(UrsineEngine::GameObject& aParent);

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
       * @param aSourceLocation The location to get highlight tiles for.
       */
      TileList GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                   const TileLocation& aSourceLocation) override;

    protected:

      /**
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                            const TileLocation& aLocation) override;

    private:
      int mRadius;
  };
}

#endif
