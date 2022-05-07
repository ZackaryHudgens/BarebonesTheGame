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
      void Select();

      /**
       * Enables or disables this skill.
       *
       * @param aEnabled Whether to enable or disable this skill.
       */
      void SetEnabled(bool aEnabled) { mEnabled = aEnabled; }

      /**
       * Returns whether this skill is enabled.
       *
       * @return Whether this skill is enabled.
       */
      bool IsEnabled() const { return mEnabled; }

    protected:

      /**
       * A virtual function that gets called during Select().
       */
      virtual void ProtectedSelect() = 0;

    private:
      bool mEnabled;
  };
}

#endif
