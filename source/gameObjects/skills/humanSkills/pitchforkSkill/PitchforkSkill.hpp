#ifndef PITCHFORKSKILL_HPP
#define PITCHFORKSKILL_HPP

#include "Skill.hpp"

namespace Barebones
{
  class PitchforkSkill : public Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The GameObject that owns this skill.
       */
      PitchforkSkill(UrsineEngine::GameObject& aParent);

      /**
       * Returns a vector of valid tile locations for executing this skill.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get valid tiles for.
       */
      TileList GetValidTiles(UrsineEngine::GameObject& aBoard,
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

      /**
       * Checks if the given location on the given board has an enemy.
       *
       * @param aBoard The board to check.
       * @param aLocation The location on the board to check.
       * @return True if there is an enemy, false otherwise.
       */
      bool IsEnemyAtLocation(UrsineEngine::GameObject& aBoard,
                             const TileLocation& aLocation);
  };
}
#endif
