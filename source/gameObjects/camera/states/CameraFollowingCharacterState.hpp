#ifndef CAMERAFOLLOWINGCHARACTERSTATE_HPP
#define CAMERAFOLLOWINGCHARACTERSTATE_HPP

#include "CameraState.hpp"

namespace Barebones
{
  class CameraFollowingCharacterState : public CameraState
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
       * Updates the state.
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> Update(double aTime) override;

      /**
       * A handler function that gets called whenever a GameObject moves in the
       * current Scene.
       *
       * @param aObject The GameObject that moved.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleObjectMoved(UrsineEngine::GameObject* aObject) override;

      /**
       * A handler function that gets called whenever a character's turn ends.
       *
       * @param aCharacter The character whose turn ended.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter) override;

    private:
      UrsineEngine::GameObject* mCharacter;

      glm::vec3 mTargetPosition;

      double mYDistance;
      double mZDistance;

      double mSpeed;

      bool mMoving;
  };
}

#endif
