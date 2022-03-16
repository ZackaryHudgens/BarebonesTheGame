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
       * A virtual function that gets called whenever this action is
       * either hovered or un-hovered.
       *
       * @param aHovered Whether this action was hovered by the user.
       */
      virtual void SetHovered(bool aHovered) = 0;

      /**
       * A virtual function that selects this action and executes it.
       */
      virtual void Select() = 0;
  };
}

#endif
