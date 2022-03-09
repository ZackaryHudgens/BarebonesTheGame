#ifndef SKILL_HPP
#define SKILL_HPP

#include <GameObject.hpp>

#include "BoardLayoutComponent.hpp"

namespace Barebones
{
  class Skill
  {
    public:

      /**
       * Constructor.
       */
      Skill();

      /**
       * A virtual function that executes this skill. Inheriting skills should
       * override this function to provide the desired behavior.
       *
       * @param aCharacter The character that is executing this skill.
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      virtual void Execute(UrsineEngine::GameObject& aCharacter,
                           UrsineEngine::GameObject& aBoard,
                           const TileLocation& aLocation) = 0;

      /**
       * A virtual function that returns a vector of valid tile locations
       * for executing this skill.
       *
       * @param aCharacter The character that is executing this skill.
       * @param aBoard A GameObject containing a BoardLayoutComponent.
       * @param aLocation The reference position.
       * @return True if the given position is valid, false otherwise.
       */
      virtual TileList GetValidTiles(UrsineEngine::GameObject& aCharacter,
                                     UrsineEngine::GameObject& aBoard,
                                     const TileLocation& aLocation) { return TileList(); }

      /**
       * Returns the name of the skill.
       *
       * @return The name of the skill.
       */
      std::string GetName() const { return mName; }

      /**
       * Returns the description of the skill.
       *
       * @return The description of the skill.
       */
      std::string GetDescription() const { return mDescription; }

    protected:

      /**
       * Sets the name of the skill.
       *
       * @param aName The name of the skill.
       */
      void SetName(const std::string& aName) { mName = aName; }

      /**
       * Sets the description of the skill.
       *
       * @param aDescription The description of the skill.
       */
      void SetDescription(const std::string& aDescription) { mDescription = aDescription; }

    private:
      std::string mDescription;
      std::string mName;
  };
}

#endif
