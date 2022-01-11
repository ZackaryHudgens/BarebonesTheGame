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

    private:
      int mHorizontalDistance;
      int mVerticalDistance;
      int mDiagonalDistance;
  };
}

#endif
