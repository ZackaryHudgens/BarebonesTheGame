#ifndef BASICHUMANBEHAVIORCOMPONENT_HPP
#define BASICHUMANBEHAVIORCOMPONENT_HPP

#include "EnemyBehaviorComponent.hpp"

namespace Barebones
{
  class BasicHumanBehaviorComponent : public EnemyBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      BasicHumanBehaviorComponent();

      /**
       * Performs an action whenever it is this character's turn.
       *
       * @param aBoard The board to take a turn on.
       */
      virtual void TakeTurn(UrsineEngine::GameObject& aBoard) override;

    private:

      /**
       * A handler function that gets called whenever a character finishes
       * moving.
       *
       * @param aCharacter The character that finished moving.
       */
      void HandleCharacterFinishedMoving(CharacterBehaviorComponent& aCharacter);

      bool mWaitingForMove;
  };
}

#endif
