#ifndef FIREBALLSPELL_HPP
#define FIREBALLSPELL_HPP

#include "Skill.hpp"

namespace Barebones
{
  class FireballSpell : public Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The GameObject that owns this skill.
       */
      FireballSpell(UrsineEngine::GameObject& aParent);

      /**
       * Returns a vector of valid tile locations for executing this skill.
       *
       * @param aBoard The board GameObject to use this skill on.
       */
      TileList GetValidTiles(UrsineEngine::GameObject& aBoard) override;

      /**
       * Returns a vector of tiles to highlight.
       *
       * @param aBoard The board GameObject to use this skill on.
       */
      TileList GetTilesToHighlight(UrsineEngine::GameObject& aBoard) override;

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
