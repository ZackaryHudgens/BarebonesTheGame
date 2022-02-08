#ifndef ACTIONBEHAVIORCOMPONENT_HPP
#define ACTIONBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

namespace Barebones
{
  class ActionBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      ActionBehaviorComponent();

      /**
       * Sets the hovered property of this action.
       *
       * @param aHovered Whether this action was hovered by the user.
       */
      void SetHovered(bool aHovered);

      /**
       * Sets the selected property of this action.
       *
       * @param aSelected Whether this action was selected by the user.
       */
      void SetSelected(bool aSelected);

    protected:

      /**
       * A virtual function that gets called whenever this action
       * is hovered over by the user.
       */
      virtual void HandleHoveredStatusChanged() = 0;

      /**
       * A virtual function that gets called whenever this action
       * is selected by the user.
       */
      virtual void HandleSelectionStatusChanged() = 0;

      bool mHovered;
      bool mSelected;
  };
}

#endif
