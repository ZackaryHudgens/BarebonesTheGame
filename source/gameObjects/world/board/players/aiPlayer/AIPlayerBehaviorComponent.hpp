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
       *
       * @param aBoard The board to take a turn on.
       */
      void ProtectedTakeTurn(UrsineEngine::GameObject& aBoard) override;

    private:
      std::vector<UrsineEngine::GameObject*> mCharacters;
      UrsineEngine::GameObject* mCurrentCharacter;

      bool mWaitingForCharacter;
  };
}

#endif
