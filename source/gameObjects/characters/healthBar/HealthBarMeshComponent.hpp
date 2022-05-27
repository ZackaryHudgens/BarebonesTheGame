#ifndef HEALTHBARMESHCOMPONENT_HPP
#define HEALTHBARMESHCOMPONENT_HPP

#include <MeshComponent.hpp>

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
  class HealthBarMeshComponent : public UrsineEngine::MeshComponent
  {
    public:

      /**
       * Constructor.
       */
      HealthBarMeshComponent();

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

      /**
       * Sets the character to display health for.
       *
       * @param aCharacter The character to display health for.
       */
      void SetCharacter(CharacterBehaviorComponent& aCharacter);

    private:

      /**
       * A handler function that gets called whenever a character's health
       * changes.
       *
       * @param aCharacter The character whose health changed.
       */
      void HandleCharacterHealthChanged(CharacterBehaviorComponent& aCharacter);

      CharacterBehaviorComponent* mCharacter;

      double mCurrentFillValue;
      double mTargetFillValue;
      double mSpeed;
      bool mMoving;

      double mBackgroundWidth;
      double mBackgroundHeight;
      double mVerticalPadding;
      double mHorizontalPadding;
  };
}

#endif
