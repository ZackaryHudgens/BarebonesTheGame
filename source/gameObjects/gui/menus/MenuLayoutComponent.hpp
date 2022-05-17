#ifndef MENULAYOUTCOMPONENT_HPP
#define MENULAYOUTCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

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
       * Adds an action to this menu by taking ownership of it and
       * adding it as a child of the parent GameObject.
       *
       * @param aObject A GameObject containing an ActionBehaviorComponent.
       */
      void AddAction(std::unique_ptr<UrsineEngine::GameObject> aObject);

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
       * Returns the actions in this menu.
       *
       * @return A vector of actions in this menu.
       */
      std::vector<UrsineEngine::GameObject*> GetActions() { return mActions; }

      /**
       * Returns the currently selected action.
       *
       * @return The currently selected action.
       */
      UrsineEngine::GameObject* GetCurrentlyHoveredAction() { return mCurrentlyHoveredAction; }

    private:
      std::vector<UrsineEngine::GameObject*> mActions;
      UrsineEngine::GameObject* mCurrentlyHoveredAction;
  };
}

#endif
