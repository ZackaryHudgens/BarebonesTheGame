#ifndef CAMERAFOLLOWINGCHARACTERSTATE_HPP
#define CAMERAFOLLOWINGCHARACTERSTATE_HPP

#include "CameraMovingState.hpp"

#include <Observer.hpp>

namespace Barebones
{
  class CameraFollowingCharacterState : public CameraMovingState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCamera The parent GameObject with a CameraBehaviorComponent.
       * @param aCharacter The character to follow.
       */
      CameraFollowingCharacterState(UrsineEngine::GameObject& aCamera,
                                    UrsineEngine::GameObject& aCharacter);

      /**
       * Gets called whenever the camera enters this state.
       */
      void OnEnter() override;

      /**
       * A handler function that gets called whenever a character's turn ends.
       *
       * @param aCharacter The character whose turn ended.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter) override;

    protected:

      /**
       * Gets called whenever the state finishes moving to the target position.
       * Can be overridden to switch to a different state.
       *
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleTargetPositionReached() override;

    private:

      /**
       * A handler function that gets called whenever a GameObject moves in the
       * current Scene.
       *
       * @param aObject The GameObject that moved.
       */
      void HandleObjectMoved(UrsineEngine::GameObject* aObject);

      UrsineEngine::GameObject* mCharacter;

      UrsineEngine::Observer mObserver;
  };
}

#endif
