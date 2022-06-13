#ifndef CAMERABEHAVIORCOMPONENT_HPP
#define CAMERABEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "HumanPlayerBehaviorComponent.hpp"

#include "CameraState.hpp"

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
       *
       * @param aTime The start time of the current Scene's Update().
       */
      void Update(double aTime) override;

      /**
       * Makes this component follow the given board.
       *
       * @param aBoard A GameObject with a BoardLayoutComponent.
       */
      void SetFollowedBoard(UrsineEngine::GameObject& aBoard);

      /**
       * Returns the board that this camera is following.
       *
       * @return The board that this camera is following, or
       *         nullptr if no board is being followed.
       */
      UrsineEngine::GameObject* GetFollowedBoard() { return mFollowedBoard; }

      /**
       * Returns the current zoom distance set by the player.
       *
       * @return The current zoom distance set by the player.
       */
      double GetZoomDistance() const { return mZoomDistance; }

    private:

      /**
       * A handler function that gets called whenever a GameObject moves.
       *
       * @param aObject The GameObject that moved.
       */
      void HandleObjectMoved(UrsineEngine::GameObject* aObject);

      /**
       * A handler function that gets called whenever a human player
       * changes location on the board.
       *
       * @param aPlayer The player that moved.
       */
      void HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer);

      /**
       * A handler function that gets called whenever a player's turn begins.
       *
       * @param aPlayer The player whose turn began.
       */
      void HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer);

      /**
       * A handler function that gets called whenever a player's turn ends.
       *
       * @param aPlayer The player whose turn ended.
       */
      void HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer);

      /**
       * A handler function that gets called whenever a character's turn begins.
       *
       * @param aCharacter The character whose turn began.
       */
      void HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever a character's turn ends.
       *
       * @param aCharacter The character whose turn ended.
       */
      void HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever the player tries
       * to zoom the camera in/out.
       *
       * @param aZoom The value to zoom by in world space.
       */
      void HandleCameraZoomChangeRequested(double aZoom);

      /**
       * A handler function that gets called whenever the act display finishes
       * its intro animation.
       *
       * @param aDisplay The act display that finished.
       */
      void HandleActDisplayFinished(UrsineEngine::GameObject& aDisplay);

      UrsineEngine::GameObject* mFollowedBoard;

      std::unique_ptr<CameraState> mState;

      double mRotation;
      double mZoomDistance;
  };
}

#endif
