#ifndef HUMANPLAYERBEHAVIORCOMPONENT_HPP
#define HUMANPLAYERBEHAVIORCOMPONENT_HPP

#include "PlayerBehaviorComponent.hpp"

#include "HumanPlayerBehaviorState.hpp"

#include "CharacterBehaviorComponent.hpp"
#include "CharacterFactory.hpp"

#include "TileUtil.hpp"

namespace Barebones
{
  class HumanPlayerBehaviorComponent : public PlayerBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      HumanPlayerBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Returns the maximum number of skeletons allowed for this player.
       *
       * @return The maximum number of skeletons allowed.
       */
      int GetMaximumSkeletons() const { return mMaxSkeletons; }

    protected:

      /**
       * A function that gets called whenever this player's turn begins.
       */
      void ProtectedTakeTurn() override;

      /**
       * A function that gets called whenever this player's turn
       * ends.
       */
      void ProtectedEndTurn() override;

      /**
       * A handler function that gets called whenever a character finishes
       * its spawning animation.
       *
       * @param aCharacter The character that finished the animation.
       */
      void HandleCharacterFinishedSpawning(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever a character starts
       * moving along a designated path.
       *
       * @param aCharacter The character that started moving.
       */
      void HandleCharacterStartedMovingAlongPath(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever a character finishes
       * moving along a designated path.
       *
       * @param aCharacter The character that finished moving.
       */
      void HandleCharacterFinishedMovingAlongPath(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever a character is
       * selected from the rewards menu.
       *
       * @param aType The type of character selected.
       */
      void HandleCharacterSelectedFromRewardsMenu(const CharacterType& aType);

      /**
       * A handler function that gets called whenever a skill is executed.
       *
       * @param aSkill The skill that was executed.
       */
      void HandleSkillExecuted(Skill& aSkill);

      /**
       * A handler function that gets called whenever a skill is cancelled.
       *
       * @param aSkill The skill that was cancelled.
       */
      void HandleSkillCancelled(Skill& aSkill);

      /**
       * A handler function that gets called whenever all characters of
       * a side on a board have been defeated.
       *
       * @param aBoard The board the characters were on.
       * @param aSide The side the characters were on.
       */
      void HandleAllCharactersOfSideDefeated(UrsineEngine::GameObject& aBoard,
                                             const Side& aSide);

    private:
      std::unique_ptr<HumanPlayerBehaviorState> mState;

      int mMaxSkeletons;
  };
}

#endif
