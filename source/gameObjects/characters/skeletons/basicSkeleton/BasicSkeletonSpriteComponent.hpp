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

    protected:

      /**
       * Loads the shaders for this skeleton.
       */
      void LoadShaders() override;

      /**
       * Loads the textures/spritesheets for this skeleton.
       */
      void LoadTextures() override;

      /**
       * Loads the animation data.
       */
      void LoadAnimations() override;
  };
}

#endif
