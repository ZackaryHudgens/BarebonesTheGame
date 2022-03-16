#ifndef SKILL_HPP
#define SKILL_HPP

#include <GameObject.hpp>

#include "TileUtil.hpp"

namespace Barebones
{
  class Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character that owns this skill.
       */
      Skill(UrsineEngine::GameObject& aCharacter);

      /**
       * A virtual function that executes this skill. Inheriting skills should
       * override this function to provide the desired behavior.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      virtual void Execute(UrsineEngine::GameObject& aBoard,
                           const TileLocation& aLocation) = 0;

      /**
       * A virtual function that returns a vector of valid tile locations
       * for executing this skill.
       *
       * @param aBoard A GameObject containing a BoardLayoutComponent.
       */
      virtual TileList GetValidTiles(UrsineEngine::GameObject& aBoard) { return TileList(); }

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
       * Returns the character that owns this skill.
       *
       * @return The character that owns this skill.
       */
      UrsineEngine::GameObject* GetCharacter() { return mCharacter; }

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
      UrsineEngine::GameObject* mCharacter;

      std::string mDescription;
      std::string mName;
  };
}

#endif
