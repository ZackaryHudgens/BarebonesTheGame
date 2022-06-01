#ifndef BONETHROWSKILL_HPP
#define BONETHROWSKILL_HPP

#include "SimpleSkill.hpp"

namespace Barebones
{
  class BoneThrowSkill : public SimpleSkill
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The GameObject that owns this skill.
       */
      BoneThrowSkill(UrsineEngine::GameObject& aParent);

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
