#ifndef REMOVECHARACTERSKILL_HPP
#define REMOVECHARACTERSKILL_HPP

#include "Skill.hpp"

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
  class RemoveCharacterSkill : public Skill
  {
    public:

      /**
       * Constructor.
       */
      RemoveCharacterSkill();

      /**
       * Returns a vector of valid tile locations for executing this skill.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get valid tiles for.
       */
      TileList GetValidTiles(UrsineEngine::GameObject& aBoard,
                             const TileLocation& aSourceLocation) override;

      /**
       * Sets the type of character to remove.
       *
       * @param aType The type of character to remove.
       */
      void SetCharacterType(const Type& aType) { mTypeToRemove = aType; }

    protected:

      /**
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                            const TileLocation& aLocation) override;

      Type mTypeToRemove;
  };
}

#endif
