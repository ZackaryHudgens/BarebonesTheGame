#ifndef BONETHROWSKILL_HPP
#define BONETHROWSKILL_HPP

#include "SimpleSkill.hpp"

namespace Barebones
{
  class BoneThrowSkill : public SimpleSkill
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character GameObject that owns this skill.
       */
      BoneThrowSkill(UrsineEngine::GameObject& aCharacter);
  };
}

#endif
