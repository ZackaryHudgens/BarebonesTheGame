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
      virtual void TakeTurn(UrsineEngine::GameObject& aBoard) override;

      /**
       * Returns a list of possible movements given a location on a board.
       *
       * @param aObject A GameObject containing a BoardLoyoutComponent.
       * @param aLocation The initial location.
       * @return A list of possible movements.
       */
      TileList GetMovements(UrsineEngine::GameObject& aObject,
                            const TileLocation& aLocation) const override;

    protected:

      /**
       * A function that gets called during Initialize().
       */
      void ProtectedInitialize() override;

    private:

      /**
       * A handler function that gets called whenever a character finishes
       * moving.
       *
       * @param aCharacter The character that finished moving.
       */
      void HandleCharacterFinishedMoving(CharacterBehaviorComponent& aCharacter);

      bool mWaitingForMove;

      int mHorizontalMovement;
      int mVerticalMovement;
  };
}

#endif
