#ifndef HINTDISPLAYBEHAVIORCOMPONENT_HPP
#define HINTDISPLAYBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "HintDisplayState.hpp"

#include "PlayerBehaviorComponent.hpp"

namespace Barebones
{
  class HintDisplayBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      HintDisplayBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

    private:

      /**
       * A handler function that gets called whenever a player's turn
       * begins.
       *
       * @param aPlayer The player whose turn began.
       */
      void HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer);

      /**
       * A handler function that gets called whenever a player's turn
       * ends.
       *
       * @param aPlayer The player whose turn ended.
       */
      void HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer);

      std::unique_ptr<HintDisplayState> mState;
  };
}

#endif
