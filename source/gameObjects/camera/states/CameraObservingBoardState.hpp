#ifndef CAMERAOBSERVINGBOARDSTATE_HPP
#define CAMERAOBSERVINGBOARDSTATE_HPP

#include "CameraState.hpp"

#include <GameObject.hpp>

namespace Barebones
{
  class CameraObservingBoardState : public CameraState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCamera The parent GameObject with a CameraBehaviorComponent.
       * @param aBoard The board object to observe.
       */
      CameraObservingBoardState(UrsineEngine::GameObject& aCamera,
                                UrsineEngine::GameObject& aBoard);

      /**
       * Updates the state.
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> Update(double aTime) override;

      /**
       * A handler function that gets called whenever a player's turn begins.
       *
       * @param aPlayer The player whose turn began.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer) override;

      /**
       * A handler function that gets called whenever a character's turn begins.
       *
       * @param aCharacter The character whose turn began.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleCharacterTurnBegan(CharacterBehaviorComponent& aCharacter) override;

    private:
      UrsineEngine::GameObject* mBoard;

      glm::vec3 mTargetPosition;

      double mYDistance;
      double mZDistance;

      double mSpeed;

      bool mMoving;
  };
}

#endif
