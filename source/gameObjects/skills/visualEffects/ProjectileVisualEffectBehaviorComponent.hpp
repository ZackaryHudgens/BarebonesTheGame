#ifndef PROJECTILEVISUALEFFECTBEHAVIORCOMPONENT_HPP
#define PROJECTILEVISUALEFFECTBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <SpriteComponent.hpp>

namespace Barebones
{
  class ProjectileVisualEffectBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      ProjectileVisualEffectBehaviorComponent(const glm::vec3& aTargetPosition,
                                              double aSpeed);

      /**
       * Updates the component.
       *
       * @param aTime The start time of the current scene's Update().
       */
      void Update(double aTime) override;

    private:
      glm::vec3 mTargetPosition;
      double mSpeed;
  };
}

#endif
