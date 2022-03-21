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

      /**
       * A virtual function that gets called by the AI player. This function
       * should be overridden to provide functionality when it is this
       * character's turn.
       *
       * @param aBoard The board to take a turn on.
       */
      virtual void TakeTurn(UrsineEngine::GameObject& aBoard) = 0;

    protected:

      /**
       * Ends this character's turn and notifies the CharacterTurnEnded Signal.
       */
      void EndTurn();
  };
}

#endif
