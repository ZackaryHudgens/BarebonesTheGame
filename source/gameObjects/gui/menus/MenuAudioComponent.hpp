#ifndef MENUAUDIOCOMPONENT_HPP
#define MENUAUDIOCOMPONENT_HPP

#include <AudioComponent.hpp>
#include <GameObject.hpp>

#include "MenuAction.hpp"

namespace Barebones
{
  class MenuAudioComponent : public UrsineEngine::AudioComponent
  {
    public:

      /**
       * Constructor.
       */
      MenuAudioComponent();

    protected:

      /**
       * A virtual function that gets called whenever a menu action is
       * hovered.
       *
       * @param aObject The GameObject that owns the MenuLayoutComponent
       *                the action belongs to.
       * @param aAction The MenuAction that was hovered.
       */
      virtual void HandleActionHovered(UrsineEngine::GameObject& aObject,
                                       const MenuAction& aAction) {}

      /**
       * A virtual function that gets called whenever a menu action is
       * executed.
       *
       * @param aObject The GameObject that owns the MenuLayoutComponent
       *                the action belongs to.
       * @param aAction The MenuAction that was executed.
       */
      virtual void HandleActionExecuted(UrsineEngine::GameObject& aObject,
                                        const MenuAction& aAction) {}
  };
}

#endif
