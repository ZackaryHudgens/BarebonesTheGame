#ifndef HINTDISPLAYSTATE_HPP
#define HINTDISPLAYSTATE_HPP

#include <GameObject.hpp>

#include "PlayerBehaviorComponent.hpp"

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
      virtual ~HintDisplayState() {};

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

      /**
       * A virtual function that gets called whenever a player's turn begins.
       *
       * @param aPlayer The player whose turn began.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<HintDisplayState> HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer) { return nullptr; }
      
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
