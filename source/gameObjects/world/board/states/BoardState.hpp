#ifndef BOARDSTATE_HPP
#define BOARDSTATE_HPP

#include <GameObject.hpp>

#include "HumanPlayerBehaviorComponent.hpp"

#include "Skill.hpp"

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
       * A virtual function that gets called whenever the board enters
       * this state.
       */
      virtual void OnEnter() {}

      /**
       * A virtual function that gets called whenever the board exits
       * this state.
       */
      virtual void OnExit() {}

      /**
       * A virtual function that gets called whenever the camera finishes
       * the initial panning sequence.
       *
       * @return A pointer to a new state, if necessary.
       */
      virtual std::unique_ptr<BoardState> HandleCameraFinishedInitialSequence() { return nullptr; }

      /**
       * A virtual function that gets called whenever a skill is selected
       * for use on the board.
       *
       * @param aSkill The skill that was selected.
       * @return A pointer to a new state, if necessary.
       */
      virtual std::unique_ptr<BoardState> HandleSkillSelected(Skill& aSkill) { return nullptr; }

      /**
       * A virtual function that gets called whenever a skill is executed
       * on the board.
       *
       * @param aSkill The skill that was executed.
       * @return A pointer to a new state, if necessary.
       */
      virtual std::unique_ptr<BoardState> HandleSkillExecuted(Skill& aSkill) { return nullptr; }

      /**
       * A virtual function that gets called whenever a skill is cancelled.
       *
       * @param aSkill The skill that was cancelled.
       * @return A pointer to a new state, if necessary.
       */
      virtual std::unique_ptr<BoardState> HandleSkillCancelled(Skill& aSkill) { return nullptr; }

      /**
       * A virtual function that gets called whenever a human player moves
       * on the board.
       *
       * @param aPlayer The player that moved.
       * @return A pointer to a new state, if necessary.
       */
      virtual std::unique_ptr<BoardState> HandleHumanPlayerMoved(HumanPlayerBehaviorComponent& aPlayer) { return nullptr; }

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
