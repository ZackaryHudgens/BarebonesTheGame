#ifndef CLAWSKILLEFFECTBEHAVIORCOMPONENT_HPP
#define CLAWSKILLEFFECTBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <SpriteComponent.hpp>

namespace Barebones
{
  class ClawSkillEffectBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      ClawSkillEffectBehaviorComponent();

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
  };
}

#endif
