#ifndef SKILLACTIONBEHAVIORCOMPONENT_HPP
#define SKILLACTIONBEHAVIORCOMPONENT_HPP

#include "ActionBehaviorComponent.hpp"

namespace Barebones
{
  class SkillActionBehaviorComponent : public ActionBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      SkillActionBehaviorComponent();

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
  };
}

#endif
