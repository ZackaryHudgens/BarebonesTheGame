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
       * Returns the actions in this menu.
       *
       * @return A vector of actions in this menu.
       */
      std::vector<MenuAction*> GetActions();

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

    protected:

      /**
       * A virtual function that gets called whenever an action is added
       * to this menu.
       */
      virtual void HandleActionAdded() {}

      /**
       * A virtual function that gets called whenever the currently hovered
       * action changes.
       */
      virtual void HandleActionHovered() {}

      /**
       * A virtual function that gets called whenever an action is executed
       * from this menu.
       */
      virtual void HandleActionExecuted() {}

      /**
       * Returns the currently selected action.
       *
       * @return The currently selected action.
       */
      MenuAction* GetCurrentlyHoveredAction() { return mCurrentlyHoveredAction; }

    private:
      std::vector<std::unique_ptr<MenuAction>> mActions;
      MenuAction* mCurrentlyHoveredAction;
  };
}

#endif
