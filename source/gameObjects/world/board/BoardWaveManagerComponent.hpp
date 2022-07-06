#ifndef BOARDWAVEMANAGERCOMPONENT_HPP
#define BOARDWAVEMANAGERCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "CharacterBehaviorComponent.hpp"
#include "CharacterFactory.hpp"

#include "Side.hpp"

namespace Barebones
{
  class BoardWaveManagerComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      BoardWaveManagerComponent();

    private:

      /**
       * Generates an encounter on the given board.
       *
       * @param aBoard The board to generate an encounter on.
       */
      void GenerateEncounter(UrsineEngine::GameObject& aBoard);

      /**
       * A handler function that gets called whenever something requests
       * a new wave of enemies on a board.
       *
       * @param aBoard The board to generate an encounter on.
       */
      void HandleNewEnemyWaveRequested(UrsineEngine::GameObject& aBoard);

      /**
       * A handler function that gets called whenever a character finishes
       * its spawning animation.
       *
       * @param aCharacter The character that finished the animation.
       */
      void HandleCharacterFinishedSpawning(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever a GameObject
       * is about to be deleted.
       *
       * @param aObject The GameObject that's about to be deleted.
       */
      void HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject);

      UrsineEngine::GameObject* mBoard;
      UrsineEngine::GameObject* mWaveDisplay;

      std::vector<UrsineEngine::GameObject*> mSpawningCharacters;

      int mWaveNumber;
      int mWavesBeforeBoss;

      static std::vector<CharacterType> mActOneEncounters;
      static std::vector<CharacterType> mActTwoEncounters;
      static std::vector<CharacterType> mActThreeEncounters;
  };
}

#endif
