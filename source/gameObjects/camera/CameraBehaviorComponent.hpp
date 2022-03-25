#ifndef CAMERABEHAVIORCOMPONENT_HPP
#define CAMERABEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "BoardLayoutComponent.hpp"

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
       */
      void Update() override;

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
       * A handler function that gets called whenever a character's turn begins.
       *
       * @param aCharacter The character whose turn began.
       */
      void HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter);

      UrsineEngine::GameObject* mFollowedBoard;

      std::unique_ptr<CameraState> mState;
  };
}

#endif
