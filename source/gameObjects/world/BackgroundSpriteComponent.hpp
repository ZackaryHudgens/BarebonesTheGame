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

    private:

      /**
       * A handler function that gets called whenever the current
       * animation advances to the next frame.
       *
       * @param aName The name of the animation.
       * @param aFrame The new current frame of the animation.
       * @param aComponent The SpriteComponent in question.
       */
      void HandleSpriteAnimationFrameChanged(const std::string& aName,
                                             int aFrame,
                                             UrsineEngine::SpriteComponent& aComponent);
  };
}

#endif
