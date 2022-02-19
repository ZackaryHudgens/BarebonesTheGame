#ifndef TURNDISPLAYCOMPONENT_HPP
#define TURNDISPLAYCOMPONENT_HPP

#include <Component.hpp>
#include <Signal.hpp>

#include "PlayerBehaviorComponent.hpp"

namespace Barebones
{
  class TurnDisplayComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      TurnDisplayComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       */
      void Update() override;

    private:
      
      /**
       * A handler function that gets called whenever a player's turn begins.
       *
       * @param aPlayer The player whose turn began.
       */
      void HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer);

      double mDisplayTime;
      double mInitialDisplayTime;

      bool mDisplayingText;
  };

  typedef UrsineEngine::SignalT<> TurnDisplayFinishedSignal;
  extern TurnDisplayFinishedSignal TurnDisplayFinished;
}

#endif
