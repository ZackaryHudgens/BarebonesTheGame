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
       * A virtual function that gets called whenever it becomes this
       * player's turn. Should be overridden by inheriting classes.
       *
       * @param aBoard The board to take a turn on.
       */
      virtual void TakeTurn(UrsineEngine::GameObject& aBoard) = 0;

      /**
       * Ends the player's turn and notifies the PlayerTurnEnded signal.
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
       * ends. Should be overridden by inheriting classes.
       */
      virtual void ProtectedEndTurn() {}

    private:
      std::string mName;
  };
}

#endif
