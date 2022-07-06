#ifndef HINTDISPLAYDEFAULTSTATE_HPP
#define HINTDISPLAYDEFAULTSTATE_HPP

#include "HintDisplayState.hpp"

namespace Barebones
{
  class HintDisplayDefaultState : public HintDisplayState
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The parent GameObject that owns this state.
       */
      HintDisplayDefaultState(UrsineEngine::GameObject& aParent);

      /**
       * A handler function that gets called whenever a player's turn begins.
       *
       * @param aPlayer The player whose turn began.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<HintDisplayState> HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer) override;
  };
}

#endif
