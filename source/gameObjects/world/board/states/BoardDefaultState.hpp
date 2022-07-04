#ifndef BOARDDEFAULTSTATE_HPP
#define BOARDDEFAULTSTATE_HPP

#include "BoardState.hpp"

#include <Observer.hpp>

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

      /**
       * Gets called whenever the board enters this state.
       */
      void OnEnter() override;

      /**
       * Gets called whenever the board exits this state.
       */
      void OnExit() override;

    private:
      
      /**
       * A handler function that gets called whenever a board changes
       * its currently focused tile.
       *
       * @param aBoard The board that changed.
       */
      void HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard);

      UrsineEngine::GameObject* mFocusedTile;
      double mHighlightIntensity;

      UrsineEngine::Observer mObserver;
  };
}

#endif
