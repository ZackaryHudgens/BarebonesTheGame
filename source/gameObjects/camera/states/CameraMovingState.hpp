#ifndef CAMERAMOVINGSTATE_HPP
#define CAMERAMOVINGSTATE_HPP

#include "CameraState.hpp"

namespace Barebones
{
  class CameraMovingState : public CameraState
  {
    public:

      /**
       * Constructor.
       *
       * @param aCamera The parent GameObject with a CameraBehaviorComponent.
       */
      CameraMovingState(UrsineEngine::GameObject& aCamera);

      /**
       * Updates the state.
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<CameraState> Update(double aTime) override;

    protected:

      /**
       * Gets called whenever the state finishes moving to the target position.
       * Can be overridden to switch to a different state.
       *
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<CameraState> HandleTargetPositionReached() { return nullptr; }

      /**
       * Sets the target position to move to.
       *
       * @param aTarget The position to move to.
       */
      void SetTargetPosition(const glm::vec3& aTarget);

      /**
       * Sets the speed at which to move.
       *
       * @param aSpeed The speed at which to move.
       */
      void SetSpeed(double aSpeed) { mSpeed = aSpeed; }

    private:
      glm::vec3 mTargetPosition;

      double mSpeed;

      bool mMoving;
  };
}

#endif
