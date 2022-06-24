#ifndef CREATECHARACTERSKILL_HPP
#define CREATECHARACTERSKILL_HPP

#include "Skill.hpp"

#include "CharacterFactory.hpp"

namespace Barebones
{
  class CreateCharacterSkill : public Skill
  {
    public:

      /**
       * Constructor.
       */
      CreateCharacterSkill();

      /**
       * Returns a vector of valid tile locations for executing this skill.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get valid tiles for.
       */
      TileList GetValidTiles(UrsineEngine::GameObject& aBoard,
                             const TileLocation& aSourceLocation) override;

      /**
       * Sets the type of character to create.
       *
       * @param aType The type of character to create.
       */
      void SetCharacterType(const CharacterType& aType) { mTypeToCreate = aType; }

    protected:

      /**
       * Selects this skill for use.
       *
       * @param aBoard The board to execute this skill on in the future.
       */
      void ProtectedSelect(UrsineEngine::GameObject& aBoard) override;

      /**
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                            const TileLocation& aLocation) override;

      /**
       * Cancels the use of this skill.
       */
      void ProtectedCancel() override;

      CharacterType mTypeToCreate;
  };
}

#endif
