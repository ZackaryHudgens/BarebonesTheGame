#ifndef CAMERABEHAVIORCOMPONENT_HPP
#define CAMERABEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "BoardLayoutComponent.hpp"

#include "PlayerBehaviorComponent.hpp"

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
       * A handler function that gets called whenever a player's
       * location changes.
       *
       * @param aPlayer The player that moved.
       */
      void HandlePlayerMoved(PlayerBehaviorComponent& aPlayer);

      /**
       * A handler function that gets called whenever a player's turn begins.
       *
       * @param aPlayer The player whose turn began.
       */
      void HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer);

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
