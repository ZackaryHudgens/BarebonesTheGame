#ifndef BOARDBEHAVIORCOMPONENT_HPP
#define BOARDBEHAVIORCOMPONENT_HPP

#include <Component.hpp>

namespace Barebones
{
  class BoardBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      BoardBehaviorComponent();

    private:

      /**
       * A handler function that gets called whenever a menu gets created.
       *
       * @param aObject The menu object that was created.
       */
      void HandleMenuCreated(UrsineEngine::GameObject& aObject);

      /**
       * A handler function that gets called whenever a menu is destroyed.
       *
       * @param aObject The menu object that was destroyed.
       */
      void HandleMenuDestroyed(UrsineEngine::GameObject& aObject);
  };
}

#endif
