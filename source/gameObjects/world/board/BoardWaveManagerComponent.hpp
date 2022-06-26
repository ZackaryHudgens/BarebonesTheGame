#ifndef BOARDWAVEMANAGERCOMPONENT_HPP
#define BOARDWAVEMANAGERCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

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
       * A handler function that gets called whenever a GameObject
       * is about to be deleted.
       *
       * @param aObject The GameObject that's about to be deleted.
       */
      void HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject);

      UrsineEngine::GameObject* mBoard;
      UrsineEngine::GameObject* mWaveDisplay;

      int mWaveNumber;

      static std::vector<CharacterType> mActOneEncounters;
      static std::vector<CharacterType> mActTwoEncounters;
      static std::vector<CharacterType> mActThreeEncounters;
  };
}

#endif
