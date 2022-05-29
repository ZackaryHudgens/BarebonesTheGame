#ifndef CHARACTERCONTROLLER_HPP
#define CHARACTERCONTROLLER_HPP

#include <GameObject.hpp>

namespace Barebones
{
  class CharacterController
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character to control.
       */
      CharacterController(UrsineEngine::GameObject& aCharacter);

      /**
       * Updates the controller.
       *
       * @param aTime The start time of the current Scene's Update().
       */
      void Update(double aTime);

      /**
       * Controls the assigned character for a turn.
       *
       * @param aBoard The board to take a turn on.
       */
      void TakeTurn(UrsineEngine::GameObject& aBoard);

    protected:

      /**
       * A virtual function that gets called during TakeTurn. Different
       * controllers need to override this function to actually control
       * the character.
       *
       * Remember to call EndTurn() when the controller is done! If you
       * don't, the assigned character's turn will never end, and the
       * game will softlock.
       *
       * @param aBoard The board to take a turn on.
       */
      virtual void ProtectedTakeTurn(UrsineEngine::GameObject& aBoard) = 0;

      /**
       * Ends the assigned character's turn by notifying the CharacterTurnEnded
       * signal.
       */
      void EndTurn();

      /**
       * Returns the assigned character.
       *
       * @return The assigned character.
       */
      UrsineEngine::GameObject* GetCharacter() { return mCharacter; }

    private:
      UrsineEngine::GameObject* mCharacter;

      double mTimeStartedEnding;
      double mEndTurnDelay;
      bool mEndingTurn;
  };
}

#endif
