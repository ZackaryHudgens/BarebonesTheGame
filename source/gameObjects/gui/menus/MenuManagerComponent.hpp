#ifndef MENUMANAGERCOMPONENT_HPP
#define MENUMANAGERCOMPONENT_HPP

#include <Component.hpp>

#include <stack>

#include "MenuLayoutComponent.hpp"

namespace Barebones
{
  class MenuManagerComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      MenuManagerComponent();

    private:

      /**
       * A handler function that gets called whenever a MenuLayoutComponent
       * is initialized.
       *
       * @param aComponent The MenuLayoutComponent that was initialized.
       */
      void HandleMenuLayoutComponentInitialized(MenuLayoutComponent& aComponent);

      /**
       * A handler function that gets called whenever a GameObject is
       * about to be deleted.
       *
       * @param aObject The GameObject about to be deleted.
       */
      void HandleObjectPendingDeletion(UrsineEngine::GameObject& aObject);

      std::stack<MenuLayoutComponent*> mMenuStack;
  };
}

#endif
