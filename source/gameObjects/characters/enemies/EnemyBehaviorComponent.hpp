#ifndef ENEMYBEHAVIORCOMPONENT_HPP
#define ENEMYBEHAVIORCOMPONENT_HPP

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
  class EnemyBehaviorComponent : public CharacterBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      EnemyBehaviorComponent();

      // TODO: create virtual function that gets called by the AI player
      // to determine and perform the best move given the board state
  };
}

#endif
