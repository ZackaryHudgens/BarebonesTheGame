#ifndef BASICHUMANSPRITECOMPONENT_HPP
#define BASICHUMANSPRITECOMPONENT_HPP

#include "CharacterSpriteComponent.hpp"

namespace Barebones
{
  class BasicHumanSpriteComponent : public CharacterSpriteComponent
  {
    public:

      /**
       * Constructor.
       */
      BasicHumanSpriteComponent();

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
