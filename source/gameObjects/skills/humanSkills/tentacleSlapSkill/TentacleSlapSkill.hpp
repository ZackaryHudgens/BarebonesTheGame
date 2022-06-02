#ifndef TENTACLESLAPSKILL_HPP
#define TENTACLESLAPSKILL_HPP

#include "SimpleSkill.hpp"

namespace Barebones
{
  class TentacleSlapSkill : public SimpleSkill
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character GameObject that owns this skill.
       */
      TentacleSlapSkill(UrsineEngine::GameObject& aCharacter);

    protected:

      /**
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                            const TileLocation& aLocation) override;
  };
}

#endif
