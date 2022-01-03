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

      /**
       * When loading, creates a number of TileObjects according to the
       * board's row and column count.
       */
      void Load() override;

      /**
       * Updates the board.
       */
      void Update() override;

    private:
      double mScaleTime;

      int mRows;
      int mColumns;

      bool mInitialized;
  };
}

#endif
