#ifndef SCREENTRANSITIONBEHAVIORCOMPONENT_HPP
#define SCREENTRANSITIONBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <MeshComponent.hpp>

#include "ScreenTransitionState.hpp"

namespace Barebones
{
  class ScreenTransitionBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      ScreenTransitionBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       *
       * @param aTime The start time of the scene's current Update().
       */
      void Update(double aTime) override;

    private:

      /**
       * A handler function that gets called whenever a screen transition to
       * another scene is requested. Once the screen transition finishes,
       * a scene of the given type is loaded.
       *
       * @param aType The type of scene to load.
       */
      void HandleScreenTransitionRequested(const SceneType& aType);

      std::unique_ptr<ScreenTransitionState> mState;
  };
}

#endif
