#ifndef PITCHFORKSKILL_HPP
#define PITCHFORKSKILL_HPP

#include "SimpleSkill.hpp"

namespace Barebones
{
  class PitchforkSkill : public SimpleSkill
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The GameObject that owns this skill.
       */
      PitchforkSkill(UrsineEngine::GameObject& aParent);
  };
}
#endif
