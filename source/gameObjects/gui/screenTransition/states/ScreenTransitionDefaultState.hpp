#ifndef SCREENTRANSITIONDEFAULTSTATE_HPP
#define SCREENTRANSITIONDEFAULTSTATE_HPP

#include "ScreenTransitionState.hpp"

namespace Barebones
{
  class ScreenTransitionDefaultState : public ScreenTransitionState
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The parent GameObject this state represents.
       */
      ScreenTransitionDefaultState(UrsineEngine::GameObject& aParent);

      /**
       * A handler function that gets called whenever a transition to a new
       * scene is requested.
       *
       * @param aType The type of scene requested.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<ScreenTransitionState> HandleScreenTransitionRequested(const SceneType& aType) override;
  };
}

#endif
