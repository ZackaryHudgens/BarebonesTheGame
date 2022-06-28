#ifndef CAMERAPANNINGTOBOARDSTATE_HPP
#define CAMERAPANNINGTOBOARDSTATE_HPP

#include "CameraMovingState.hpp"

namespace Barebones
{
  class CameraPanningToBoardState : public CameraMovingState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCamera The parent GameObject with a CameraBehaviorComponent.
       */
      CameraPanningToBoardState(UrsineEngine::GameObject& aCamera);

      /**
       * Gets called whenever the camera enters this state.
       */
      void OnEnter() override;

    protected:

      /**
       * Gets called whenever the state finishes moving to the target position.
       * Can be overridden to switch to a different state.
       *
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> HandleTargetPositionReached() override;
  };
}

#endif
