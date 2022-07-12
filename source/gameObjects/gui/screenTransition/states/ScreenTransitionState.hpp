#ifndef SCREENTRANSITIONSTATE_HPP
#define SCREENTRANSITIONSTATE_HPP

#include <GameObject.hpp>

#include "SceneFactory.hpp"

namespace Barebones
{
  class ScreenTransitionState
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The parent GameObject this state represents.
       */
      ScreenTransitionState(UrsineEngine::GameObject& aParent);
      virtual ~ScreenTransitionState() {}

      /**
       * A virtual function that gets called whenever the parent enters
       * this state.
       */
      virtual void OnEnter() {}

      /**
       * A virtual function that gets called whenever the parent exits
       * this state.
       */
      virtual void OnExit() {}

      /**
       * A virtual function that updates the state.
       *
       * @param aTime The start time of the current Scene's Update().
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<ScreenTransitionState> Update(double aTime) { return nullptr; }

      /**
       * A virtual function that gets called whenever a transition to a new
       * scene is requested.
       *
       * @param aType The type of scene requested.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<ScreenTransitionState> HandleScreenTransitionRequested(const SceneType& aType) { return nullptr; }

    protected:

      /**
       * Returns the parent GameObject.
       *
       * @return The parent GameObject.
       */
      UrsineEngine::GameObject* GetParent() const { return mParent; }

    private:
      UrsineEngine::GameObject* mParent;
  };
}

#endif
