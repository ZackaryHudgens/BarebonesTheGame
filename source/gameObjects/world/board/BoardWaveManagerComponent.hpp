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
       * A handler function that gets called whenever all characters of
       * a side on a board have been defeated.
       *
       * @param aBoard The board the characters were on.
       * @param aSide The side the characters were on.
       */
      void HandleAllCharactersOfSideDefeated(UrsineEngine::GameObject& aBoard,
                                             const Side& aSide);
      int mWaveNumber;

      static std::vector<CharacterType> mActOneEncounters;
      static std::vector<CharacterType> mActTwoEncounters;
      static std::vector<CharacterType> mActThreeEncounters;
  };
}

#endif
