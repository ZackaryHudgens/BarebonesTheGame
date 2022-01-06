#ifndef CHARACTERSPRITECOMPONENT_HPP
#define CHARACTERSPRITECOMPONENT_HPP

#include <SpriteComponent.hpp>

namespace Barebones
{
  class CharacterSpriteComponent : public UrsineEngine::SpriteComponent
  {
    public:

      /**
       * Constructor.
       */
      CharacterSpriteComponent();

      /**
       * Initializes the component, along with any shaders, textures,
       * and animations, by calling the protected virtual functions.
       */
      void Initialize() override;

    protected:

      /**
       * Sets up any necessary textures.
       */
      virtual void SetupTextures() {};

      /**
       * Sets up any necessary shaders.
       */
      virtual void SetupShaders() {};

      /**
       * Sets up any necessary animations.
       */
      virtual void SetupAnimations() {};
  };
}

#endif
