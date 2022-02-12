#ifndef SKILLACTIONBEHAVIORCOMPONENT_HPP
#define SKILLACTIONBEHAVIORCOMPONENT_HPP

#include "ActionBehaviorComponent.hpp"

#include "CharacterSkillComponent.hpp"

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
      void SetSkill(CharacterSkillComponent& aSkill);

      /**
       * Returns the name of the current skill.
       *
       * @return The name of the current skill.
       */
      std::string GetSkillName() const;

      /**
       * Returns the description of the current skill.
       *
       * @return The description of the current skill.
       */
      std::string GetSkillDescription() const;

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
      CharacterSkillComponent* mSkill;
  };
}

#endif
