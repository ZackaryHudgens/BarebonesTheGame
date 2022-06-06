#ifndef CLAWSKILL_HPP
#define CLAWSKILL_HPP

#include "SingleTargetSkill.hpp"

namespace Barebones
{
  class ClawSkill : public SingleTargetSkill
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character GameObject that owns this skill.
       */
      ClawSkill(UrsineEngine::GameObject& aCharacter);

    protected:

      /**
       * Creates visual effects before executing this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void PreExecute(UrsineEngine::GameObject& aBoard,
                      const TileLocation& aLocation) override;
  };
}

#endif
