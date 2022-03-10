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
       */
      MoveSkill();

      /**
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void Execute(UrsineEngine::GameObject& aBoard,
                   const TileLocation& aLocation) override;

      /**
       * Returns a vector of valid tile locations for executing this skill.
       *
       * @param aBoard A GameObject containing a BoardLayoutComponent.
       * @param aLocation The reference position.
       * @return True if the given position is valid, false otherwise.
       */
      TileList GetValidTiles(UrsineEngine::GameObject& aBoard,
                             const TileLocation& aLocation) override;
  };
}

#endif
