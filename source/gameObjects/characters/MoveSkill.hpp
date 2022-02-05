#ifndef MOVESKILL_HPP
#define MOVESKILL_HPP

#include "CharacterSkill.hpp"

namespace Barebones
{
  class MoveSkill : public CharacterSkill
  {
    public:

      /**
       * Constructor.
       */
      MoveSkill();

      /**
       * A handler function that gets called whenever the user selects
       * this skill.
       */
      void Select() override;

      /**
       * A handler function that gets called whenever the user executes
       * this skill.
       */
      void Esecute() override;
  };
}

#endif
