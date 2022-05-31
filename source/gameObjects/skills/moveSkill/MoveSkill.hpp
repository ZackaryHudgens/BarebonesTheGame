#ifndef MOVESKILL_HPP
#define MOVESKILL_HPP

#include "Skill.hpp"

#include "MoveSkillEffectBehaviorComponent.hpp"

namespace Barebones
{
  class MoveSkill : public Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The GameObject that owns this skill.
       */
      MoveSkill(UrsineEngine::GameObject& aParent);

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
       * Selects this skill for use.
       *
       * @param aBoard The board to execute this skill on in the future.
       */
      void ProtectedSelect(UrsineEngine::GameObject& aBoard) override;

      /**
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                            const TileLocation& aLocation) override;

      /**
       * Cancels the use of this skill.
       */
      void ProtectedCancel() override;

      /**
       * A handler function that gets called during SetEnabled().
       *
       * @param aEnabled Whether this skill was enabled or disabled.
       */
      void HandleEnabledChanged(bool aEnabled) override;

    private:
      MoveSkillEffectBehaviorComponent* mSkillEffect;

      TilePathList mShortestPaths;

      int mDistanceRemaining;
  };
}

#endif
