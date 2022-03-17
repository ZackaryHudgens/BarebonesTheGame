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
       * @param aCharacter The character that owns this skill.
       */
      MoveSkill(UrsineEngine::GameObject& aCharacter);

      /**
       * Returns a vector of valid tile locations for executing this skill.
       *
       * @param aBoard A GameObject containing a BoardLayoutComponent.
       */
      TileList GetValidTiles(UrsineEngine::GameObject& aBoard) override;

    protected:

      /**
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                            const TileLocation& aLocation) override;
  };
}

#endif
