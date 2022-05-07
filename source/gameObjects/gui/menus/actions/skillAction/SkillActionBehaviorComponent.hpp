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
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Hovers or un-hovers the action.
       *
       * @param aHovered Whether this action was hovered by the user.
       */
      void SetHovered(bool aHovered) override;

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
       * Selects this action.
       */
      void ProtectedSelect() override;

    private:
      Skill* mSkill;
  };
}

#endif
