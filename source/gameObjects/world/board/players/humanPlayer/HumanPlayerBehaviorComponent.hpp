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

      /**
       * Sets the location of the player on the board.
       *
       * @param aLocation The new location of the player.
       */
      void SetLocation(const TileLocation& aLocation);

      /**
       * Returns the location of the player on the board.
       *
       * @return The location of the player.
       */
      TileLocation GetLocation() const { return mLocation; }

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

    private:
      UrsineEngine::GameObject* mBoard;
      TileLocation mLocation;

      CreateCharacterSkill mCreateSkill;
      RemoveCharacterSkill mRemoveSkill;

      int mMaxSkeletons;

      bool mWaitingForCharacterRemoval;
      bool mWaitingToSelectCreateSkill;
  };
}

#endif
