#ifndef CAMERASTATE_HPP
#define CAMERASTATE_HPP

#include <GameObject.hpp>

#include "CharacterBehaviorComponent.hpp"
#include "PlayerBehaviorComponent.hpp"

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
      virtual ~CameraState() {}

      /**
       * A virtual function that gets called whenever the camera enters
       * this state.
       */
      virtual void OnEnter() {}

      /**
       * A virtual function that gets called whenever the camera exits
       * this state.
       */
      virtual void OnExit() {}

      /**
       * A virtual function that updates the state.
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> Update(double aTime);

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

      /**
       * A virtual function that gets called whenever the act display finishes
       * its intro animation.
       *
       * @param aDisplay The act display that finished.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> HandleActDisplayFinished(UrsineEngine::GameObject& aDisplay);

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
