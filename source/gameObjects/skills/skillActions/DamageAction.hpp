#ifndef DAMAGEACTION_HPP
#define DAMAGEACTION_HPP

#include "SkillAction.hpp"

namespace Barebones
{
  class DamageAction : public SkillAction
  {
    public:

      /**
       * Constructor.
       */
      DamageAction();

      /**
       * Performs this action at the given location on the given board.
       *
       * @param aBoard The board to perform this action on.
       * @param aLocation The location to perform this action at.
       */
      void Execute(UrsineEngine::GameObject& aBoard,
                   const TileLocation& aLocation) override;

      /**
       * Sets the base damage for this action.
       *
       * @param aDamage The base damage for this action.
       */
      void SetDamage(int aDamage) { mDamage = aDamage; }

      /**
       * Returns the base damage for this action.
       *
       * @return The base damage for this action.
       */
      int GetDamage() const { return mDamage; }

    private:
      int mDamage;
  };
}

#endif
