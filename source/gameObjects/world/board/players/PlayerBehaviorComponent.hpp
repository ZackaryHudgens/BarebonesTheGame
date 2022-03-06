#ifndef PLAYERBEHAVIORCOMPONENT_HPP
#define PLAYERBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

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
       * Returns the name of the player.
       *
       * @return The name of the player.
       */
      std::string GetName() const { return mName; }

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
  };
}

#endif
