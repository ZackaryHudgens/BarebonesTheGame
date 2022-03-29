#ifndef CAMERASTATE_HPP
#define CAMERASTATE_HPP

#include <GameObject.hpp>

#include "CharacterBehaviorComponent.hpp"
#include "HumanPlayerBehaviorComponent.hpp"

namespace Barebones
{
  class CameraState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCamera The parent GameObject with a CameraBehaviorComponent.
       */
      CameraState(UrsineEngine::GameObject& aCamera);

      /**
       * A virtual function that updates the state.
       *
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> Update();

      /**
       * A virtual function that gets called whenever a GameObject moves in the
       * current Scene.
       *
       * @param aObject The GameObject that moved.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> HandleObjectMoved(UrsineEngine::GameObject* aObject);

      /**
       * A virtual function that gets called whenever the parent camera
       * starts following a new board object.
       *
       * @param aBoard The newly-followed board object.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> HandleBoardFollowed(UrsineEngine::GameObject& aBoard);

      /**
       * A virtual function that gets called whenever a human player
       * changes location on the board.
       *
       * @param aPlayer The player that moved.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer);

      /**
       * A virtual function that gets called whenever a player's turn begins.
       *
       * @param aPlayer The player whose turn began.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer);

      /**
       * A virtual function that gets called whenever a player's turn ends.
       *
       * @param aPlayer The player whose turn ended.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer);

      /**
       * A virtual function that gets called whenever a character's turn begins.
       *
       * @param aCharacter The character whose turn began.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter);

      /**
       * A virtual function that gets called whenever a character's turn ends.
       *
       * @param aCharacter The character whose turn ended.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter);

    protected:

      /**
       * Returns the camera object.
       *
       * @return The camera object.
       */
      UrsineEngine::GameObject* GetCamera() { return mCamera; }

    private:
      UrsineEngine::GameObject* mCamera;
  };
}

#endif
