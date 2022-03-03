#ifndef BACKGROUNDSPRITECOMPONENT_HPP
#define BACKGROUNDSPRITECOMPONENT_HPP

#include <SpriteComponent.hpp>

namespace Barebones
{
  class BackgroundSpriteComponent : public UrsineEngine::SpriteComponent
  {
    public:

      /**
       * Constructor.
       */
      BackgroundSpriteComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;
  };
}

#endif
