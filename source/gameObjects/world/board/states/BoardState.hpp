#ifndef BOARDSTATE_HPP
#define BOARDSTATE_HPP

#include <GameObject.hpp>

namespace Barebones
{
  class BoardState
  {
    public:

      /**
       * Constructor.
       *
       * @param aBoard The board this state represents.
       */
      BoardState(UrsineEngine::GameObject& aBoard);
      virtual ~BoardState() {}

      /**
       * A virtual function that gets called each time the board object updates.
       * Returns a pointer to a new state, if necessary.
       *
       * @param aTime The start time of the current scene's Update().
       */
      virtual std::unique_ptr<BoardState> Update(double aTime) { return nullptr; }

    protected:

      /**
       * Returns the board object this state represents.
       *
       * @return The board object this state represents.
       */
      UrsineEngine::GameObject* GetBoard() const { return mBoard; }

    private:
      UrsineEngine::GameObject* mBoard;
  };
}

#endif
