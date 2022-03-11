#ifndef PLAYERBEHAVIORCOMPONENT_HPP
#define PLAYERBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>
#include <Signal.hpp>

#include "TileUtil.hpp"

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
       * Returns the name of the player.
       *
       * @return The name of the player.
       */
      std::string GetName() const { return mName; }

      /**
       * Sets the location of the player on the board.
       *
       * @param aLocation The new location of the player.
       */
      void SetLocation(const TileLocation& aLocation);

      /**
       * Returns the location of the player on the board.
       *
       * @return The location of the player.
       */
      TileLocation GetLocation() const { return mLocation; }

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

    protected:

      /**
       * Sets the name of the player.
       *
       * @param aName The new name of the player.
       */
      void SetName(const std::string& aName) { mName = aName; }

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
      std::string mName;

      TileLocation mLocation;
  };

  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerMovedSignal;
  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerTurnBeganSignal;
  typedef UrsineEngine::SignalT<PlayerBehaviorComponent&> PlayerTurnEndedSignal;

  extern PlayerMovedSignal     PlayerMoved;
  extern PlayerTurnBeganSignal PlayerTurnBegan;
  extern PlayerTurnEndedSignal PlayerTurnEnded;
}

#endif
