#ifndef BASICSKELETONSPRITECOMPONENT_HPP
#define BASICSKELETONSPRITECOMPONENT_HPP

#include <SpriteComponent.hpp>

namespace Barebones
{
  class BasicSkeletonSpriteComponent : public UrsineEngine::SpriteComponent
  {
    public:

      /**
       * Constructor.
       */
      BasicSkeletonSpriteComponent();

      /**
       * Loads the sprites and animations for the basic skeleton.
       */
      void Load() override;
  };
}

#endif
