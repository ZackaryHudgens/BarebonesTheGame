#ifndef MAINMENUAUDIOCOMPONENT_HPP
#define MAINMENUAUDIOCOMPONENT_HPP

#include "MenuAudioComponent.hpp"

namespace Barebones
{
  class BasicMenuAudioComponent : public MenuAudioComponent
  {
    public:

      /**
       * Constructor.
       */
      BasicMenuAudioComponent();

    protected:

      /**
       * A handler function that gets called whenever a menu action is
       * hovered.
       *
       * @param aObject The GameObject that owns the MenuLayoutComponent
       *                the action belongs to.
       * @param aAction The MenuAction that was hovered.
       */
      void HandleActionHovered(UrsineEngine::GameObject& aObject,
                               const MenuAction& aAction) override;

      /**
       * A handler function that gets called whenever a menu action is
       * executed.
       *
       * @param aObject The GameObject that owns the MenuLayoutComponent
       *                the action belongs to.
       * @param aAction The MenuAction that was executed.
       */
      void HandleActionExecuted(UrsineEngine::GameObject& aObject,
                                const MenuAction& aAction) override;
  };
}

#endif
