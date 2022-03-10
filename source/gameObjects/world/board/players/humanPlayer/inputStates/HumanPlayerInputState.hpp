#ifndef HUMANPLAYERINPUTSTATE_HPP
#define HUMANPLAYERINPUTSTATE_HPP

#include <CoreSignals.hpp>
#include <GameObject.hpp>

namespace Barebones
{
  class HumanPlayerInputState
  {
    public:

      /**
       * Constructor.
       *
       * @param aPlayer The player GameObject to handle input for.
       */
      HumanPlayerInputState(UrsineEngine::GameObject& aPlayer);

      /**
       * Sets the board GameObject to operate on.
       *
       * @param aBoard The board to operate on.
       */
      void SetBoard(UrsineEngine::GameObject& aBoard) { mBoard = &aBoard; }

      /**
       * A virtual function that gets called whenever the user presses
       * a key. Should be overridden by inheriting states.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      virtual std::unique_ptr<HumanPlayerInputState> HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                      int aMods) { return nullptr; }

      /**
       * A virtual function that gets called whenever the user holds
       * a key down long enough to repeat the input. Should be overridden
       * by inheriting states.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      virtual std::unique_ptr<HumanPlayerInputState> HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                       int aMods) { return nullptr; }

    protected:

      /**
       * Returns the player GameObject that this state is handling input for.
       *
       * @return The player GameObject.
       */
      UrsineEngine::GameObject* GetPlayer() { return mPlayer; }

      /**
       * Returns the board GameObject.
       *
       * @return The board GameObject.
       */
      UrsineEngine::GameObject* GetBoard() { return mBoard; }

    private:
      UrsineEngine::GameObject* mPlayer;
      UrsineEngine::GameObject* mBoard;
  };
}

#endif
