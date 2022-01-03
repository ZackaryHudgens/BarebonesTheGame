#ifndef BOARDBEHAVIORCOMPONENT_HPP
#define BOARDBEHAVIORCOMPONENT_HPP

#include <Component.hpp>

namespace Barebones
{
  class BoardBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      BoardBehaviorComponent();

    private:
      int mRows;
      int mColumns;
  };
}

#endif
