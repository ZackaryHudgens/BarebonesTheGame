#ifndef SKILLFACTORY_HPP
#define SKILLFACTORY_HPP

#include "Skill.hpp"

namespace Barebones
{
  enum class SkillType
  {
    eCLAW,
    eBONE_THROW,
    eTENTACLE_SLAP
  };

  class SkillFactory
  {
    public:

      /**
       * Returns a skill with the proper actions attached based on
       * the type of skill given.
       *
       * @param aType The type of skill to create.
       * @return A unique pointer to a new skill.
       */
      static std::unique_ptr<Skill> CreateSkill(const SkillType& aType);
  };

  class SkillVisualEffectFactory
  {
    public:

      /**
       * Returns a skill with the proper actions attached based on
       * the type of skill given.
       *
       * @param aType The type of skill to create.
       * @return A unique pointer to a new skill.
       */
      static std::unique_ptr<Skill> CreateSkill(const SkillType& aType);
  };
}

#endif
