#ifndef BASICSKELETONSPRITECOMPONENT_HPP
#define BASICSKELETONSPRITECOMPONENT_HPP

#include "CharacterSpriteComponent.hpp"

namespace Barebones
{
  class BasicSkeletonSpriteComponent : public CharacterSpriteComponent
  {
    public:

      /**
       * Constructor.
       */
      BasicSkeletonSpriteComponent();

      /**
       */

    protected:

      /**
       * Sets up any necessary shaders.
       */
      void SetupShaders() override;

      /**
       * Sets up any necessary textures.
       */
      void SetupTextures() override;

      /**
       * Sets up any necessary animations.
       */
      void SetupAnimations() override;
  };
}

#endif
