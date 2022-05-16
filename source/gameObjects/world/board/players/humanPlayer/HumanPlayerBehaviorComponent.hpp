#ifndef HUMANPLAYERBEHAVIORCOMPONENT_HPP
#define HUMANPLAYERBEHAVIORCOMPONENT_HPP

#include "PlayerBehaviorComponent.hpp"

#include "Skill.hpp"
#include "TileUtil.hpp"

#include "CharacterBehaviorComponent.hpp"

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

      /**
       * Returns a vector of this player's spells.
       *
       * @return This player's spells.
       */
      std::vector<Skill*> GetSpells();

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
       * Adds a spell to this player.
       *
       * @param aSpell The spell to add.
       */
      void AddSpell(std::unique_ptr<Skill> aSpell);

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

    private:
      TileLocation mLocation;

      std::vector<std::unique_ptr<Skill>> mSpells;

      bool mTakingTurn;
  };
}

#endif
