#ifndef SKILLACTIONBEHAVIORCOMPONENT_HPP
#define SKILLACTIONBEHAVIORCOMPONENT_HPP

#include "ActionBehaviorComponent.hpp"

#include "Skill.hpp"

namespace Barebones
{
  class SkillActionBehaviorComponent : public ActionBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      SkillActionBehaviorComponent();

      /**
       * Sets the skill that this action represents.
       *
       * @param aSkill The skill that this action represents.
       */
      void SetSkill(Skill& aSkill);

      /**
       * Returns a pointer to the skill that this action represents.
       *
       * @return The skill that this action represents.
       */
      Skill* GetSkill() { return mSkill; }

    protected:

      /**
       * Executes this action.
       */
      void ProtectedExecute() override;

    private:
      Skill* mSkill;
  };
}

#endif
