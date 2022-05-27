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

    protected:

      /**
       * A protected function that gets called during Initialize().
       */
      void ProtectedInitialize() override;
  };
}

#endif
