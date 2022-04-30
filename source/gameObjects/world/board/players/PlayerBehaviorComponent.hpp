#ifndef PLAYERBEHAVIORCOMPONENT_HPP
#define PLAYERBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "Side.hpp"

namespace Barebones
{
  /**
   * The PlayerBehaviorComponent provides an interface for defining different
   * types of players (i.e. human or artificial).
   */
  class PlayerBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      PlayerBehaviorComponent();

      /**
       * Tells the player to take a turn.
       *
       * @param aBoard The board to take a turn on.
       */
      void TakeTurn(UrsineEngine::GameObject& aBoard);

      /**
       * Ends the player's turn.
       */
      void EndTurn();

      /**
       * Sets the side that this player controls.
       *
       * @param aSide The side this player should control.
       */
      void SetSide(const Side& aSide) { mControlledSide = aSide; }

      /**
       * Returns the side that this player controls.
       *
       * @return The side that this player controls.
       */
      Side GetSide() const { return mControlledSide; }

    protected:

      /**
       * A virtual function that gets called whenever this player's turn
       * begins. Should be overridden by inheriting classes.
       *
       * @param aBoard The board to take a turn on.
       */
      virtual void ProtectedTakeTurn(UrsineEngine::GameObject& aBoard) {}

      /**
       * A virtual function that gets called whenever this player's turn
       * ends. Should be overridden by inheriting classes.
       */
      virtual void ProtectedEndTurn() {}

    private:
      Side mControlledSide;
  };
}

#endif
