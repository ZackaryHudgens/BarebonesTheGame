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
       * A virtual function that gets called whenever it becomes
       * this player's turn. Should be overridden by inheriting classes.
       *
       * @param aBoard The board to take a turn on.
       */
      virtual void TakeTurn(UrsineEngine::GameObject& aBoard) {}
  };
}

#endif
