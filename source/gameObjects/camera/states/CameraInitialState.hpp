#ifndef CAMERAINITIALSTATE_HPP
#define CAMERAINITIALSTATE_HPP

#include "CameraState.hpp"

namespace Barebones
{
  class CameraInitialState : public CameraState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCamera The parent GameObject with a CameraBehaviorComponent.
       */
      CameraInitialState(UrsineEngine::GameObject& aCamera);

      /**
       * Gets called whenever the camera enters this state.
       */
      void OnEnter() override;

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
