#ifndef PITCHFORKSKILL_HPP
#define PITCHFORKSKILL_HPP

#include "SingleTargetSkill.hpp"

namespace Barebones
{
  class PitchforkSkill : public SingleTargetSkill
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character GameObject that owns this skill.
       */
      PitchforkSkill(UrsineEngine::GameObject& aCharacter);
  };
}
#endif
