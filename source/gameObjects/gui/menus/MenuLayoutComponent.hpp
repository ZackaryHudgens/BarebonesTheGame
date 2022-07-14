#ifndef MENULAYOUTCOMPONENT_HPP
#define MENULAYOUTCOMPONENT_HPP

#include <Component.hpp>

#include "MenuAction.hpp"

namespace Barebones
{
  class MenuLayoutComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      MenuLayoutComponent();

      /**
       * Adds an action to this menu.
       *
       * @param aAction The action to add.
       */
      void AddAction(std::unique_ptr<MenuAction> aAction);

      /**
       * Hovers over the next action in the list.
       */
      void HoverOverNextAction();

      /**
       * Hovers over the previous action in the list.
       */
      void HoverOverPreviousAction();

      /**
       * Executes the currently hovered action.
       */
      void ExecuteCurrentAction();

      /**
       * Sets whether to wrap around to the first/last action when using
       * HoverOverNextAction() or HoverOverPreviousAction().
       *
       * @param aWraparound Whether to wrap around at the end of the
       *                    action list.
       */
      void SetWraparoundEnabled(bool aWraparound) { mWraparound = aWraparound; }

      /**
       * Returns whether wraparound is enabled for this menu.
       *
       * @return Whether wraparound is enabled for this menu.
       */
      bool IsWraparoundEnabled() const { return mWraparound; }

    protected:

      /**
       * A virtual function that gets called whenever an action is added
       * to this menu.
       *
       * @param aAction The action that was added.
       */
      virtual void HandleActionAdded(MenuAction& aAction) {}

      /**
       * A virtual function that gets called whenever the currently hovered
       * action changes.
       *
       * @param aAction The action that was hovered.
       */
      virtual void HandleActionHovered(MenuAction& aAction) {}

      /**
       * A virtual function that gets called whenever an action is executed
       * from this menu.
       *
       * @param aAction The action that was executed.
       */
      virtual void HandleActionExecuted(MenuAction& aAction) {}

      /**
       * A virtual function that gets called whenever an action in this menu
       * is enabled or disabled.
       *
       * @param aAction The action that changed.
       */
      virtual void HandleActionEnabledChanged(MenuAction& aAction) {}

    private:

      /**
       * A handler function that gets called whenever a MenuAction is enabled
       * or disabled.
       *
       * @param aAction The action that changed.
       */
      void HandleMenuActionEnabledChanged(MenuAction& aAction);

      std::vector<std::unique_ptr<MenuAction>> mActions;
      MenuAction* mCurrentlyHoveredAction;

      bool mWraparound;
  };
}

#endif
