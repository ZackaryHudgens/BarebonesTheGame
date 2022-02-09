#ifndef MENUBEHAVIORCOMPONENT_HPP
#define MENUBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <Signal.hpp>

namespace Barebones
{
  class MenuBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      MenuBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

    private:

      /**
       * A handler function that gets called whenever a GameObject
       * is about to be deleted.
       *
       * @param aObject The object in question.
       */
      void HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject);
  };

  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> MenuCreatedSignal;
  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> MenuDestroyedSignal;

  extern MenuCreatedSignal   MenuCreated;
  extern MenuDestroyedSignal MenuDestroyed;
}

#endif
