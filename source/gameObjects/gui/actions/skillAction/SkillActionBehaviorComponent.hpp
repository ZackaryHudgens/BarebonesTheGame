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
       * A handler function that gets called whenever this action
       * is hovered over by the user.
       */
      void HandleHoveredStatusChanged() override;

      /**
       * A handler function that gets called whenever this action
       * is selected by the user.
       */
      void HandleSelectionStatusChanged() override;

    private:
      Skill* mSkill;
  };
}

#endif
