#ifndef FIREBALLSPELLEFFECTBEHAVIORCOMPONENT_HPP
#define FIREBALLSPELLEFFECTBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <SpriteComponent.hpp>

namespace Barebones
{
  class FireballSpellEffectBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      FireballSpellEffectBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       *
       * @param aTime The start time of the current scene's Update().
       */
      void Update(double aTime) override;

    private:
      UrsineEngine::SpriteComponent* mSprite;

      double mScaleSpeed;
  };
}

#endif
