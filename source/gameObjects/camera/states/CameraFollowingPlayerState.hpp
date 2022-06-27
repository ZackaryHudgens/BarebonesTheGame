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
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> Update(double aTime) override;

      /**
       * A handler function that gets called whenever the board's focused
       * tile changes.
       *
       * @param aBoard The board that updated.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard) override;

      /**
       * A handler function that gets called whenever a player's turn ends.
       *
       * @param aPlayer The player whose turn ended.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer) override;

    private:
      UrsineEngine::GameObject* mPlayer;

      glm::vec3 mTargetPosition;

      double mYDistance;
      double mZDistance;

      double mSpeed;

      bool mMoving;
  };
}

#endif
