#ifndef BASICSKELETONBEHAVIORCOMPONENT_HPP
#define BASICSKELETONBEHAVIORCOMPONENT_HPP

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
  class BasicSkeletonBehaviorComponent : public CharacterBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      BasicSkeletonBehaviorComponent();

      /**
       * Updates the component.
       */
      void Update() override;

    private:

      /**
       * A handler function that gets called whenever the selection
       * status of this character changes.
       *
       * @param aSelected Whether this character was selected.
       */
      void HandleSelectionChanged(bool aSelected) override;

      double mGlowSpeed;
      double mTimeBeganGlowing;
  };
}

#endif
