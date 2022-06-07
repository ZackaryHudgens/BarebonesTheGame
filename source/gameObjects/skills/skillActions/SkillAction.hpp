#ifndef SKILLACTION_HPP
#define SKILLACTION_HPP

#include <GameObject.hpp>

#include "TileUtil.hpp"

namespace Barebones
{
  class SkillAction
  {
    public:

      /**
       * Constructor.
       */
      SkillAction();

      /**
       * A virtual function that performs this action at the given location
       * on the given board.
       *
       * @param aBoard The board to perform this action on.
       * @param aLocation The location to perform this action at.
       */
      virtual void Execute(UrsineEngine::GameObject& aBoard,
                           const TileLocation& aLocation) = 0;
  };
}

#endif
