#ifndef HUMANPLAYEREDITINGBEHAVIORSTATE_HPP
#define HUMANPLAYEREDITINGBEHAVIORSTATE_HPP

#include "HumanPlayerBehaviorState.hpp"

#include "CreateCharacterSkill.hpp"
#include "RemoveCharacterSkill.hpp"

namespace Barebones
{
  class HumanPlayerEditingBehaviorState : public HumanPlayerBehaviorState
  {
    public:

      /**
       * Constructor.
       *
       * @param aPlayer The human player this state represents.
       * @param aType The type of character to create with the CreateCharacterSkill.
       */
      HumanPlayerEditingBehaviorState(UrsineEngine::GameObject& aPlayer,
                                      const CharacterType& aType);

      /**
       * Gets called when the player enters this state.
       */
      void OnEnter() override;

      /**
       * Gets called when the player exits this state.
       */
      void OnExit() override;

      /**
       * A handler function that gets called whenever a skill is executed.
       *
       * @param aSkill The skill that was executed.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<HumanPlayerBehaviorState> HandleSkillExecuted(Skill& aSkill) override;

      /**
       * A handler function that gets called whenever a skill is cancelled.
       *
       * @param aSkill The skill that was cancelled.
       * @return A unique_ptr to a new state, if necessary.
       */
      std::unique_ptr<HumanPlayerBehaviorState> HandleSkillCancelled(Skill& aSkill) override;

    private:
      CreateCharacterSkill mCreateSkill;
      RemoveCharacterSkill mRemoveSkill;

      Skill* mSelectedSkill;
  };
}

#endif
