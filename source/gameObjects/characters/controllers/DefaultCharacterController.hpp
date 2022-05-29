#ifndef DEFAULTCHARACTERCONTROLLER_HPP
#define DEFAULTCHARACTERCONTROLLER_HPP

#include "CharacterController.hpp"

#include <Observer.hpp>

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
  class DefaultCharacterController : public CharacterController
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character to control.
       */
      DefaultCharacterController(UrsineEngine::GameObject& aCharacter);

    protected:

      /**
       * A function that gets called during TakeTurn().
       *
       * @param aBoard The board to take a turn on.
       */
      void ProtectedTakeTurn(UrsineEngine::GameObject& aBoard) override;

    private:

      /**
       * A handler function that gets called when a character finishes
       * moving along a path.
       *
       * @param aCharacter The character that finished moving.
       */
      void HandleCharacterFinishedMovingAlongPath(CharacterBehaviorComponent& aCharacter);

      UrsineEngine::Observer mObserver;
      bool mWaitingForMove;
  };
}

#endif
