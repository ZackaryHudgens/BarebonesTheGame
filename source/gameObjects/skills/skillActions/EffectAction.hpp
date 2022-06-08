#ifndef EFFECTACTION_HPP
#define EFFECTACTION_HPP

#include "SkillAction.hpp"

namespace Barebones
{
  enum class EffectType
  {
    eNONE,
    eSLOW
  };

  class EffectAction : public SkillAction
  {
    public:

      /**
       * Constructor.
       */
      EffectAction();

      /**
       * Performs this action at the given location on the given board.
       *
       * @param aBoard The board to perform this action on.
       * @param aLocation The location to perform this action at.
       */
      void Execute(UrsineEngine::GameObject& aBoard,
                   const TileLocation& aLocation) override;

      /**
       * Sets the type of effect to apply for this action.
       *
       * @param aType The type of effect to apply.
       */
      void SetEffectType(const EffectType& aType) { mType = aType; }

      /**
       * Returns the type of effect this action applies.
       *
       * @return The type of effect this action applies.
       */
      EffectType GetEffectType() const { return mType; }

    private:
      EffectType mType;
  };
}

#endif
