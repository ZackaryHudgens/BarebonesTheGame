#ifndef SLASHSKILL_HPP
#define SLASHSKILL_HPP

#include "Skill.hpp"

namespace Barebones
{
  class SlashSkill : public Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character that owns this skill.
       */
      SlashSkill(UrsineEngine::GameObject& aCharacter);

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
