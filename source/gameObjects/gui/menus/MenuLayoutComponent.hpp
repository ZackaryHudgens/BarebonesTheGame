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
       * Initializes the component.
       */
      void Initialize() override;

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

      /**
       * Sets whether this menu is hidden. In order for this function to
       * do anything, HandleHiddenStatusChanged() needs to be overridden.
       *
       * @param aHidden The new hidden status of the menu.
       */
      void SetHidden(bool aHidden);

      /**
       * Returns the hidden status of this menu.
       *
       * @return The hidden status of this menu.
       */
      bool IsHidden() const { return mHidden; }

    protected:

      /**
       * A virtual function that gets called during Initialize().
       */
      virtual void ProtectedInitialize() {}

      /**
       * A virtual function that gets called whenever the hidden status of
       * this menu changes.
       *
       * @param aHidden The new hidden status of the menu.
       */
      virtual void HandleHiddenStatusChanged(bool aHidden) {}

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
       * A virtual function that gets called whenever an action in this menu
       * is enabled or disabled.
       *
       * @param aAction The action that changed.
       */
      virtual void HandleActionEnabledChanged(MenuAction& aAction) {}

      /**
       * Returns the currently selected action.
       *
       * @return The currently selected action.
       */
      MenuAction* GetCurrentlyHoveredAction() { return mCurrentlyHoveredAction; }

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

      bool mHidden;
  };
}

#endif
