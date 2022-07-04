#ifndef BOARDINITIALSTATE_HPP
#define BOARDINITIALSTATE_HPP

#include "BoardState.hpp"

namespace Barebones
{
  class BoardInitialState : public BoardState
  {
    public:

      /**
       * Constructor.
       *
       * @param aBoard The board this state represents.
       */
      BoardInitialState(UrsineEngine::GameObject& aBoard);

      /**
       * Gets called whenever the board exits this state.
       */
      void OnExit() override;

      /**
       * A handler function that gets called whenever the camera finishes
       * the initial panning sequence.
       *
       * @return A pointer to a new state, if necessary.
       */
      std::unique_ptr<BoardState> HandleCameraFinishedInitialSequence() override;
  };
}

#endif
