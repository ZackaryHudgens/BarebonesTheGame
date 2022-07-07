#ifndef HUMANPLAYERBEHAVIORSTATE_HPP
#define HUMANPLAYERBEHAVIORSTATE_HPP

#include <GameObject.hpp>

namespace Barebones
{
  class CharacterBehaviorComponent;
  class CharacterType;
  class Skill;

  class HumanPlayerBehaviorState
  {
    public:

      /**
       * Constructor.
       *
       * @param aPlayer The human player this state represents.
       */
      HumanPlayerBehaviorState(UrsineEngine::GameObject& aPlayer);
      virtual ~HumanPlayerBehaviorState() {}

      /**
       * A virtual function that gets called when the player
       * enters this state.
       */
      virtual void OnEnter() {}

      /**
       * A virtual function that gets called when the player
       * exits this state.
       */
      virtual void OnExit() {}

      /**
       * A virtual function that gets called whenever a character finishes
       * its spawning animation.
       *
       * @param aCharacter The character that finished the animation.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<HumanPlayerBehaviorState> HandleCharacterFinishedSpawning(CharacterBehaviorComponent& aCharacter) { return nullptr; }

      /**
       * A virtual function that gets called whenever a character is
       * selected from the rewards menu.
       *
       * @param aType The type of character selected.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<HumanPlayerBehaviorState> HandleCharacterSelectedFromRewardsMenu(const CharacterType& aType) { return nullptr; }

      /**
       * A virtual function that gets called whenever a skill is executed.
       *
       * @param aSkill The skill that was executed.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<HumanPlayerBehaviorState> HandleSkillExecuted(Skill& aSkill) { return nullptr; }

      /**
       * A virtual function that gets called whenever a skill is cancelled.
       *
       * @param aSkill The skill that was cancelled.
       * @return A unique_ptr to a new state, if necessary.
       */
      virtual std::unique_ptr<HumanPlayerBehaviorState> HandleSkillCancelled(Skill& aSkill) { return nullptr; }

    protected:

      /**
       * Returns the player this state represents.
       *
       * @return The player this state represents.
       */
      UrsineEngine::GameObject* GetPlayer() const { return mPlayer; }

    private:
      UrsineEngine::GameObject* mPlayer;
  };
}

#endif
