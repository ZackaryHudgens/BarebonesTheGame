#ifndef SPELL_HPP
#define SPELL_HPP

#include <GameObject.hpp>

#include "TileUtil.hpp"

namespace Barebones
{
  class Spell
  {
    public:

      /**
       * Constructor.
       *
       * @param aPlayer The human player that owns this skill.
       */
      Spell(UrsineEngine::GameObject& aPlayer);

      /**
       * Executes this spell.
       *
       * @param aBoard The board to execute this spell on.
       * @param aLocation The location on the board to execute this spell.
       */
      void Execute(UrsineEngine::GameObject& aBoard,
                   const TileLocation& aLocation);
  };
}

#endif
