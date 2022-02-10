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
       * of this tile changes.
       */
      void HandleHighlightChanged() override;

    private:
      double mScale;
      double mScaleSpeed;

      bool mScaling;
  };
}

#endif
