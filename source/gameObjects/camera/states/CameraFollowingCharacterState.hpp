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
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> Update() override;

    private:

      /**
       * A handler function that gets called whenever a GameObject's position changes.
       *
       * @param aObject The object that moved.
       */
      void HandleObjectMoved(UrsineEngine::GameObject* aObject);

      UrsineEngine::GameObject* mCharacter;
  };
}

#endif
