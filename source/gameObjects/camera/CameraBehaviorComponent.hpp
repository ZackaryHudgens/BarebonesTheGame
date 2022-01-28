#ifndef CAMERABEHAVIORCOMPONENT_HPP
#define CAMERABEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "TileBehaviorComponent.hpp"

namespace Barebones
{
  class CameraBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      CameraBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       */
      void Update() override;

    private:

      /**
       * A handler function that gets called whenever a tile is
       * hovered.
       *
       * @param aTile The tile that was hovered over.
       */
      void HandleTileHovered(TileBehaviorComponent& aTile);

      glm::vec3 mTargetPosition;

      double mYDistance;
      double mZDistance;
      double mRotation;

      double mSpeed;

      bool mMoving;
  };
}

#endif
