#ifndef PLAYERBEHAVIORCOMPONENT_HPP
#define PLAYERBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>
#include <Signal.hpp>

namespace Barebones
{
  class PlayerBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      PlayerBehaviorComponent();

      /**
       * Tells this component to begin taking a turn.
       *
       * @param aBoard The board to take a turn on.
       */
      void TakeTurn(UrsineEngine::GameObject& aBoard);

      /**
       * Tells this component to end its turn.
       */
      void EndTurn();

    protected:

      /**
       * A virtual function that gets called whenever it becomes this
       * player's turn. Should be overridden by inheriting classes.
       *
       * @param aBoard The board to take a turn on.
       */
      virtual void ProtectedTakeTurn(UrsineEngine::GameObject& aBoard) {}

      /**
       * A virtual function that gets called whenever this player's turn
       * ends. Should be overridden by inheriting classes.
       */
      virtual void ProtectedEndTurn() {}
  };

  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerTurnBeganSignal;
  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerTurnEndedSignal;

  extern PlayerTurnBeganSignal   PlayerTurnBegan;
  extern PlayerTurnEndedSignal   PlayerTurnEnded;
}

#endif
