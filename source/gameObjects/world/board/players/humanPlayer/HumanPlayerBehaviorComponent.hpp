#ifndef HUMANPLAYERBEHAVIORCOMPONENT_HPP
#define HUMANPLAYERBEHAVIORCOMPONENT_HPP

#include "PlayerBehaviorComponent.hpp"

#include "Skill.hpp"
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
       * Returns a vector of this player's skills.
       *
       * @return This player's skills.
       */
      std::vector<Skill*> GetSkills();

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
       * Adds a skill to this player.
       *
       * @param aSkill The skill to add.
       */
      void AddSkill(std::unique_ptr<Skill> aSkill);

    private:
      TileLocation mLocation;

      std::vector<std::unique_ptr<Skill>> mSkills;
  };
}

#endif
