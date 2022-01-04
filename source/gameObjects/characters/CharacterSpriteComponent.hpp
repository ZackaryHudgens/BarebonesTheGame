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
       * Loads the component, along with any shaders, textures,
       * and animations, by calling the protected virtual functions.
       */
      void Load() override;

    protected:

      /**
       * Loads any necessary textures.
       */
      virtual void LoadTextures() {};

      /**
       * Loads any necessary shaders.
       */
      virtual void LoadShaders() {};

      /**
       * Loads any animations.
       */
      virtual void LoadAnimations() {};
  };
}

#endif
