#ifndef DEFAULTTILEBEHAVIORCOMPONENT_HPP
#define DEFAULTTILEBEHAVIORCOMPONENT_HPP

#include <GameObject.hpp>

#include "TileBehaviorComponent.hpp"

namespace Barebones
{
  class DefaultTileBehaviorComponent : public TileBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      DefaultTileBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       */
      void Update() override;

    protected:

      /**
       * A handler function that gets called whenever the highlight status
       * changes.
       *
       * @param aHighlighted Whether this tile is being highlighted.
       */
      void HandleHighlightChanged(bool aHighlighted) override;

    private:
      double mScale;
      double mScaleSpeed;

      bool mScaling;
  };
}

#endif
