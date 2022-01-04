#ifndef CHARACTERBEHAVIORCOMPONENT_HPP
#define CHARACTERBEHAVIORCOMPONENT_HPP

#include <map>

#include <Component.hpp>

namespace Barebones
{
  class CharacterBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      CharacterBehaviorComponent();

      /**
       * Sets the character's board position.
       *
       * @param aXPos The x position to move to.
       * @param aYPos The y position to move to.
       */
      void SetBoardPosition(int aXPos,
                            int aYPos);

      /**
       * Returns the character's board position.
       *
       * @return The character's board position.
       */
      std::pair<int, int> GetBoardPosition() const { return mBoardPosition; }

    private:
      std::pair<int, int> mBoardPosition;
  };
}

#endif
