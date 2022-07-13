#ifndef SKILLACTION_HPP
#define SKILLACTION_HPP

#include <GameObject.hpp>

#include "TileUtil.hpp"

namespace Barebones
{
  class SkillAction
  {
    public:

      /**
       * Constructor.
       */
      SkillAction();
      virtual ~SkillAction() {};

      /**
       * A virtual function that performs this action at the given location
       * on the given board.
       *
       * @param aBoard The board to perform this action on.
       * @param aLocation The location to perform this action at.
       */
      virtual void Execute(UrsineEngine::GameObject& aBoard,
                           const TileLocation& aLocation) = 0;

      /**
       * Returns the description of this action. This is used to inform the
       * player of what the action does, i.e. "Deals x damage".
       *
       * @return The description of this action.
       */
      std::string GetDescription() const { return mDescription; }

    protected:

      /**
       * Sets the description of this action.
       *
       * @param aDescription The description of this action.
       */
      void SetDescription(const std::string& aDescription) { mDescription = aDescription; }

    private:
      std::string mDescription;
  };
}

#endif
