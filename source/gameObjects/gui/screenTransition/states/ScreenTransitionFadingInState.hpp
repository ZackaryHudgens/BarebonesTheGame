#ifndef SCREENTRANSITIONFADINGINSTATE_HPP
#define SCREENTRANSITIONFADINGINSTATE_HPP

#include "ScreenTransitionState.hpp"

namespace Barebones
{
  class ScreenTransitionFadingInState : public ScreenTransitionState
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The parent GameObject this state represents.
       */
      ScreenTransitionFadingInState(UrsineEngine::GameObject& aParent);

      /**
       * Gets called whenever the parent enters this state.
       */
      void OnEnter() override;

      /**
       * Gets called whenever the parent exits this state.
       */
      void OnExit() override;

      /**
       * Updates the state.
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<ScreenTransitionState> Update(double aTime) override;

    private:
      double mSpeed;
      double mFadeValue;
  };
}

#endif
