#ifndef CAMERAFOLLOWINGPLAYERSTATE_HPP
#define CAMERAFOLLOWINGPLAYERSTATE_HPP

#include "CameraMovingState.hpp"

#include <Observer.hpp>

namespace Barebones
{
  class CameraFollowingPlayerState : public CameraMovingState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCamera The parent GameObject with a CameraBehaviorComponent.
       * @param aPlayer The player to follow.
       */
      CameraFollowingPlayerState(UrsineEngine::GameObject& aCamera,
                                 PlayerBehaviorComponent& aPlayer);

      /**
       * Gets called whenever the camera enters this state.
       */
      void OnEnter() override;

      /**
       * A handler function that gets called whenever a player's turn ends.
       *
       * @param aPlayer The player whose turn ended.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer) override;

    private:
      
      /**
       * A handler function that gets called whenever a board changes
       * its currently focused tile.
       *
       * @param aBoard The board that changed.
       */
      void HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard);

      PlayerBehaviorComponent* mPlayer;

      UrsineEngine::Observer mObserver;
  };
}

#endif
