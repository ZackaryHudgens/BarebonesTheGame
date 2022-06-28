#ifndef CAMERADEFAULTSTATE_HPP
#define CAMERADEFAULTSTATE_HPP

#include "CameraState.hpp"

#include <Observer.hpp>

namespace Barebones
{
  class CameraDefaultState : public CameraState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCamera The parent GameObject with a CameraBehaviorComponent.
       */
      CameraDefaultState(UrsineEngine::GameObject& aCamera);

      /**
       * A virtual function that gets called whenever a player's turn begins.
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

      /**
       * A handler function that gets called whenever the act display finishes
       * its intro animation.
       *
       * @param aDisplay The act display that finished.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleActDisplayFinished(UrsineEngine::GameObject& aDisplay) override;
  };
}

#endif
