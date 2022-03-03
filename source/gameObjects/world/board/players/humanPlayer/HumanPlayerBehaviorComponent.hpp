#ifndef HUMANPLAYERBEHAVIORCOMPONENT_HPP
#define HUMANPLAYERBEHAVIORCOMPONENT_HPP

#include "PlayerBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

namespace Barebones
{
  class HumanPlayerBehaviorComponent : public PlayerBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      HumanPlayerBehaviorComponent();

    protected:

      /**
       * A function that gets called whenever this player's turn begins.
       */
      void ProtectedTakeTurn() override;

      /**
       * A function that gets called whenever this player's turn
       * ends.
       */
      void ProtectedEndTurn() override;
  };
}

#endif
