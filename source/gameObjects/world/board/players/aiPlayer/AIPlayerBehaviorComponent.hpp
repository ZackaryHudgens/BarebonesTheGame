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
       *
       * @param aTime The start time of the current Scene's Update().
       */
      void Update(double aTime) override;

    protected:

      /**
       * A function that gets called whenever this player's turn begins.
       */
      void ProtectedTakeTurn() override;

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

      bool mWaitingToTakeTurn;
  };
}

#endif
