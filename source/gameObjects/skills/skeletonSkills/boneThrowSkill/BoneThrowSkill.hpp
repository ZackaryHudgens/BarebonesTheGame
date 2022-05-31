#ifndef BONETHROWSKILL_HPP
#define BONETHROWSKILL_HPP

#include "Skill.hpp"

namespace Barebones
{
  class BoneThrowSkill : public Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The GameObject that owns this skill.
       */
      BoneThrowSkill(UrsineEngine::GameObject& aParent);
  };
}

#endif
