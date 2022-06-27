#ifndef HUMANPLAYERBEHAVIORCOMPONENT_HPP
#define HUMANPLAYERBEHAVIORCOMPONENT_HPP

#include "PlayerBehaviorComponent.hpp"

#include "TileUtil.hpp"

#include "CharacterBehaviorComponent.hpp"
#include "CharacterFactory.hpp"

#include "CreateCharacterSkill.hpp"
#include "RemoveCharacterSkill.hpp"

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
       * Updates the component.
       *
       * @param aTime The start time of the current scene's Update().
       */
      void Update(double aTime) override;

    protected:

      /**
       * A function that gets called whenever this player's turn begins.
       *
       * @param aBoard The board to take a turn on.
       */
      void ProtectedTakeTurn(UrsineEngine::GameObject& aBoard) override;

      /**
       * A function that gets called whenever this player's turn
       * ends.
       */
      void ProtectedEndTurn() override;

      /**
       * A handler function that gets called whenever the board has finished
       * placing and loading tiles, and is ready to add characters to.
       *
       * @param aBoard The board that finished.
       */
      void HandleBoardFinishedInitialSequence(UrsineEngine::GameObject& aBoard);

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
       * A handler function that gets called whenever all characters of
       * a side on a board have been defeated.
       *
       * @param aBoard The board the characters were on.
       * @param aSide The side the characters were on.
       */
      void HandleAllCharactersOfSideDefeated(UrsineEngine::GameObject& aBoard,
                                             const Side& aSide);

    private:
      std::vector<CharacterType> mSkeletonInventory;
      int mMaxSkeletons;

      UrsineEngine::GameObject* mBoard;

      CreateCharacterSkill mCreateSkill;
      RemoveCharacterSkill mRemoveSkill;

      bool mWaitingForCharacterRemoval;
      bool mWaitingToSelectCreateSkill;
  };
}

#endif
