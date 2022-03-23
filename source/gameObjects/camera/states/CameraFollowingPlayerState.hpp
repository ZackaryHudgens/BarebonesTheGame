#ifndef CAMERAFOLLOWINGPLAYERSTATE_HPP
#define CAMERAFOLLOWINGPLAYERSTATE_HPP

#include "CameraState.hpp"

namespace Barebones
{
  class CameraFollowingPlayerState : public CameraState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCamera The parent GameObject with a CameraBehaviorComponent.
       * @param aPlayer The player to follow.
       */
      CameraFollowingPlayerState(UrsineEngine::GameObject& aCamera,
                                 UrsineEngine::GameObject& aPlayer);

      /**
       * Updates the state.
       *
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> Update() override;

      /**
       * A handler function that gets called whenever a human player
       * changes location on the board.
       *
       * @param aPlayer The player that moved.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer) override;

    private:
      UrsineEngine::GameObject* mPlayer;

      glm::vec3 mTargetPosition;

      double mYDistance;
      double mZDistance;
      double mRotation;

      double mSpeed;

      bool mMoving;
  };
}

#endif
