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
      virtual void SetHovered(bool aHovered) {};

      /**
       * Executes this action.
       */
      void Execute();

      /**
       * Enables or disables this action. Disabled actions can't be selected.
       *
       * @param aEnabled Whether to enable or disable this action.
       */
      void SetEnabled(bool aEnabled) { mEnabled = aEnabled; }

      /**
       * Returns whether this action is enabled.
       *
       * @return True if this action is enabled, false if it's disabled.
       */
      bool IsEnabled() const { return mEnabled; }

    protected:

      /**
       * A virtual function that gets called during Execute().
       *
       * This must be overridden to provide functionality when the user
       * chooses this action.
       */
      virtual void ProtectedExecute() = 0;

    private:
      bool mEnabled;
  };
}

#endif
