#ifndef AIPLAYERBEHAVIORCOMPONENT_HPP
#define AIPLAYERBEHAVIORCOMPONENT_HPP

#include "PlayerBehaviorComponent.hpp"

namespace Barebones
{
  class AIPlayerBehaviorComponent : public PlayerBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      AIPlayerBehaviorComponent();

    protected:

      /**
       * A function that gets called whenever this player's turn begins.
       */
      void ProtectedTakeTurn() override;
  };
}

#endif
