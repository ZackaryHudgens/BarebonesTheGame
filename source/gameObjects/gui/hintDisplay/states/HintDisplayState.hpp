#ifndef HINTDISPLAYSTATE_HPP
#define HINTDISPLAYSTATE_HPP

#include <GameObject.hpp>

namespace Barebones
{
  class HintDisplayState
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The parent GameObject that owns this state.
       */
      HintDisplayState(UrsineEngine::GameObject& aParent);

      /**
       * A virtual function that gets called by the hint display when
       * it enters this state.
       */
      virtual void OnEnter() {};

      /**
       * A virtual function that gets called by the hint display when
       * it exits this state.
       */
      virtual void OnExit() {};
      
    protected:

      /**
       * Returns the parent GameObject.
       *
       * @return The parent GameObject.
       */
      UrsineEngine::GameObject* GetParent() { return mParent; }

    private:
      UrsineEngine::GameObject* mParent;
  };
}

#endif
