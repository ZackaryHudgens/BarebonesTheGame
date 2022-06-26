#ifndef BOARDWAITINGFORCAMERASTATE_HPP
#define BOARDWAITINGFORCAMERASTATE_HPP

#include "BoardState.hpp"

#include <Observer.hpp>

namespace Barebones
{
  class BoardWaitingForCameraState : public BoardState
  {
    public:

      /**
       * Constructor.
       *
       * @param aBoard The board this state represents.
       */
      BoardWaitingForCameraState(UrsineEngine::GameObject& aBoard);

      /**
       * Gets called each time the board object updates.
       * Returns a pointer to a new state, if necessary.
       *
       * @param aTime The start time of the current scene's Update().
       */
      std::unique_ptr<BoardState> Update(double aTime) override;

    private:

      /**
       * A handler function that gets called whenever the camera finishes
       * moving to observe a board.
       *
       * @param aBoard The board the camera moved to.
       */
      void HandleCameraFinishedMovingToBoard(UrsineEngine::GameObject& aBoard);

      UrsineEngine::Observer mObserver;

      bool mWaiting;
  };
}

#endif
