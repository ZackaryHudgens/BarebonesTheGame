#ifndef SKELETONSPRITECOMPONENT_HPP
#define SKELETONSPRITECOMPONENT_HPP

#include <SpriteComponent.hpp>

namespace Barebones
{
  class SkeletonSpriteComponent : public UrsineEngine::SpriteComponent
  {
    public:

      /**
       * Constructor.
       */
      SkeletonSpriteComponent();

      /**
       * Loads the component, along with any shaders, textures,
       * and animations, by calling the protected virtual functions.
       */
      void Load() override;

    protected:

      /**
       * Loads the shaders for this skeleton.
       */
      virtual void LoadShaders() {};

      /**
       * Loads the textures/spritesheets for this skeleton.
       */
      virtual void LoadTextures() {};

      /**
       * Loads the animation data.
       */
      virtual void LoadAnimations() {};
  };
}

#endif
