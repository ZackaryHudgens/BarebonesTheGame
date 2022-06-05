#ifndef COLORCHANGEVISUALEFFECTBEHAVIORCOMPONENT_HPP
#define COLORCHANGEVISUALEFFECTBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

namespace Barebones
{
  class ColorChangeVisualEffectBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character whose color to change.
       * @param aColor The color to turn the character.
       * @param aSpeed The speed at which to change the color.
       */
      ColorChangeVisualEffectBehaviorComponent(UrsineEngine::GameObject& aCharacter,
                                               const glm::vec3& aColor,
                                               double aSpeed);

      /**
       * Updates the component.
       *
       * @param aTime The start time of the current scene's Update().
       */
      void Update(double aTime) override;

    private:
      UrsineEngine::GameObject* mCharacter;
      glm::vec3 mColor;
      double mSpeed;

      double mFadeValue;
      bool mFadingIn;
  };
}

#endif
