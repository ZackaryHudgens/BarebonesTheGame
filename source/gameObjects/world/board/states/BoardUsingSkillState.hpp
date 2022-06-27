#ifndef BOARDUSINGSKILLSTATE_HPP
#define BOARDUSINGSKILLSTATE_HPP

#include "BoardState.hpp"

namespace Barebones
{
  class BoardUsingSkillState : public BoardState
  {
    public:

      /**
       * Constructor.
       *
       * @param aBoard The board this state represents.
       * @param aSkill The skill being used.
       */
      BoardUsingSkillState(UrsineEngine::GameObject& aBoard,
                           Skill& aSkill);

      /**
       * Gets called whenever the board enters this state.
       */
      void OnEnter() override;

      /**
       * Gets called whenever the board exits this state.
       */
      void OnExit() override;

      /**
       * A handler function that gets called whenever a skill is executed
       * on the board.
       *
       * @param aSkill The skill that was executed.
       * @return A pointer to a new state, if necessary.
       */
      std::unique_ptr<BoardState> HandleSkillExecuted(Skill& aSkill) override;

      /**
       * A virtual function that gets called whenever a skill is cancelled.
       *
       * @param aSkill The skill that was cancelled.
       * @return A pointer to a new state, if necessary.
       */
      std::unique_ptr<BoardState> HandleSkillCancelled(Skill& aSkill) override;

    private:
      Skill* mSkill;
      std::vector<UrsineEngine::GameObject*> mHighlightedTiles;
  };
}

#endif
