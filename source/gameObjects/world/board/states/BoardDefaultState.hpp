#ifndef BOARDDEFAULTSTATE_HPP
#define BOARDDEFAULTSTATE_HPP

#include "BoardState.hpp"

namespace Barebones
{
  class BoardDefaultState : public BoardState
  {
    public:

      /**
       * Constructor.
       *
       * @param aBoard The board this state represents.
       */
      BoardDefaultState(UrsineEngine::GameObject& aBoard);
  };
}

#endif
