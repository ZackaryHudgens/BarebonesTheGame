#ifndef AIPLAYERBEHAVIORCOMPONENT_HPP
#define AIPLAYERBEHAVIORCOMPONENT_HPP

#include "PlayerBehaviorComponent.hpp"

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
  class AIPlayerBehaviorComponent : public PlayerBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      AIPlayerBehaviorComponent();

      /**
       * Updates the component.
       */
      void Update() override;

    protected:

      /**
       * A function that gets called whenever this player's turn begins.
       *
       * @param aBoard The board to take a turn on.
       */
      void ProtectedTakeTurn(UrsineEngine::GameObject& aBoard) override;

      /**
       * A handler function that gets called whenever a character finishes
       * taking a turn.
       *
       * @param aCharacter The character that ended its turn.
       */
      void HandleCharacterTurnEnded(CharacterBehaviorComponent& aCharacter);

    private:
      std::vector<UrsineEngine::GameObject*> mCharacters;
      UrsineEngine::GameObject* mCurrentCharacter;
      UrsineEngine::GameObject* mBoard;

      bool mWaitingToTakeTurn;
  };
}

#endif
