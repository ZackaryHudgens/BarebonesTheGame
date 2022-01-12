#ifndef CAMERABEHAVIORCOMPONENT_HPP
#define CAMERABEHAVIORCOMPONENT_HPP

#include <Component.hpp>

namespace Barebones
{
  class CameraBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      CameraBehaviorComponent();

      /**
       * Centers the camera on the given board.
       *
       * @param aObject The GameObject to center on.
       */
      void CenterOnBoard(UrsineEngine::GameObject& aObject);

    private:
      double mHeight;
      double mZDistance;
      double mRotation;
  };
}

#endif
