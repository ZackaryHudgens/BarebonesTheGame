#ifndef TILEBEHAVIORCOMPONENT_HPP
#define TILEBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

namespace Barebones
{
  class TileBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      TileBehaviorComponent();

      /**
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       *
       * @param aTime The start time of the current Scene's Update().
       */
      void Update(double aTime) override;

      /**
       * A virtual function that gets called whenever a character stops
       * moving on this tile.
       *
       * @param aCharacter The character GameObject that stopped moving.
       */
      virtual void HandleCharacterEntered(UrsineEngine::GameObject& aCharacter) {}

      /**
       * A virtual function that gets called whenever a character moves away
       * from this tile.
       *
       * @param aCharacter The character GameObject that moved away.
       */
      virtual void HandleCharacterExited(UrsineEngine::GameObject& aCharacter) {}

      /**
       * A virtual function that gets called whenever a character ends the turn
       * on this tile.
       *
       * @param aCharacter The character GameObject that ended the turn on this tile.
       */
      virtual void HandleTurnEnded(UrsineEngine::GameObject& aCharacter) {}

      /**
       * A virtual function that gets called whenever a character begins the turn
       * on this tile.
       *
       * @param aCharacter The character GameObject that begins the turn on this tile.
       */
      virtual void HandleTurnBegan(UrsineEngine::GameObject& aCharacter) {}

      /**
       * Sets the color to use when highlighting this tile.
       *
       * @param aColor The color to use when highlighting.
       */
      void SetHighlightColor(const glm::vec3& aColor);

      /**
       * Sets the intensity of the highlight color, on a scale from 0.0 to 1.0.
       *
       * @param aIntensity The intensity of the highlight color.
       */
      void SetHighlightIntensity(double aIntensity);

    private:
      float mFadeValue;
      double mFadeSpeed;

      bool mFadingIn;
  };
}

#endif
