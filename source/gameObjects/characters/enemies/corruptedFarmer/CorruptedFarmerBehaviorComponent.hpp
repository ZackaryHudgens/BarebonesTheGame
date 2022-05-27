#ifndef CORRUPTEDFARMERBEHAVIORCOMPONENT_HPP
#define CORRUPTEDFARMERBEHAVIORCOMPONENT_HPP

#include "EnemyBehaviorComponent.hpp"

namespace Barebones
{
  class CorruptedFarmerBehaviorComponent : public EnemyBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      CorruptedFarmerBehaviorComponent();

      /**
       * Performs an action whenever it is this character's turn.
       *
       * @param aBoard The board to take a turn on.
       */
      void TakeTurn(UrsineEngine::GameObject& aBoard) override;

    protected:

      /**
       * A function that gets called during Initialize().
       */
      void ProtectedInitialize() override;

    private:

      /**
       * A handler function that gets called whenever a character finishes
       * moving along a path.
       *
       * @param aCharacter The character that finished moving.
       */
      void HandleCharacterFinishedMovingAlongPath(CharacterBehaviorComponent& aCharacter);

      bool mWaitingForMove;
  };
}

#endif
