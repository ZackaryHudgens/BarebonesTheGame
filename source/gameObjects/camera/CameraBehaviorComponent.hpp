#ifndef CAMERABEHAVIORCOMPONENT_HPP
#define CAMERABEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "BoardLayoutComponent.hpp"

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

      /**
       * Makes this component follow the given board.
       *
       * @param aBoard A GameObject with a BoardLayoutComponent.
       */
      void FollowBoard(UrsineEngine::GameObject& aBoard);

    private:

      /**
       * A handler function that gets called whenever the player's
       * location on the board changes.
       *
       * @param aLocation The new location on the board.
       */
      void HandlePlayerMoved(const TileLocation& aLocation);

      UrsineEngine::GameObject* mFollowedBoard;

      glm::vec3 mTargetPosition;

      double mYDistance;
      double mZDistance;
      double mRotation;

      double mSpeed;

      bool mMoving;
  };
}

#endif
