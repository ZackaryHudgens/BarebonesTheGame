#ifndef ANIMATIONVISUALEFFECTBEHAVIORCOMPONENT_HPP
#define ANIMATIONVISUALEFFECTBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <SpriteComponent.hpp>

namespace Barebones
{
  class AnimationVisualEffectBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       *
       * @param aSpritesheet The spritesheet used for the animation.
       * @param aClips A vector of clips that make up the animation.
       * @param aSpeed The speed of the animation.
       */
      AnimationVisualEffectBehaviorComponent(const std::string& aSpritesheet,
                                             const std::vector<UrsineEngine::TextureClip> aClips,
                                             double aSpeed);

      /**
       * Initializes the component.
       */
      void Initialize() override;

    private:

      /**
       * A handler function that gets called whenever a sprite animation
       * completes.
       *
       * @param aName The name of the animation that finished.
       * @param aSprite The SpriteComponent that finished animating.
       */
      void HandleSpriteAnimationComplete(const std::string& aName,
                                         UrsineEngine::SpriteComponent& aSprite);

      UrsineEngine::SpriteComponent* mSprite;

      std::string mSpritesheet;
      std::vector<UrsineEngine::TextureClip> mClips;
      double mSpeed;
  };
}

#endif
