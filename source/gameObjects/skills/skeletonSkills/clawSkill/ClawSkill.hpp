#ifndef CLAWSKILL_HPP
#define CLAWSKILL_HPP

#include "SimpleSkill.hpp"

namespace Barebones
{
  class ClawSkill : public SimpleSkill
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
       * Creates a visual effect for this skill and returns it as a
       * std::unique_ptr.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       * @return A visual effect for this skill.
       */
      std::unique_ptr<UrsineEngine::GameObject> CreateVisualEffect(UrsineEngine::GameObject& aBoard,
                                                                   const TileLocation& aLocation) override;
  };
}

#endif
