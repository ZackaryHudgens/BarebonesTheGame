#ifndef DESECRATEDTILEBEHAVIORCOMPONENT_HPP
#define DESECRATEDTILEBEHAVIORCOMPONENT_HPP

#include <GameObject.hpp>

#include "TileBehaviorComponent.hpp"

namespace Barebones
{
  class DesecratedTileBehaviorComponent : public TileBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      DesecratedTileBehaviorComponent();

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
       * A handler function that gets called whenever a character stops
       * moving on this tile.
       *
       * @param aCharacter The character GameObject that stopped moving.
       */
      void HandleCharacterEntered(UrsineEngine::GameObject& aCharacter) override;

      /**
       * A handler function that gets called whenever a character moves away
       * from this tile.
       *
       * @param aCharacter The character GameObject that moved away.
       */
      void HandleCharacterExited(UrsineEngine::GameObject& aCharacter) override;

    protected:

      /**
       * A handler function that gets called whenever the highlight status
       * of this tile changes.
       *
       * @param aHighlight Whether this tile should be highlighted.
       */
      void HandleHighlightChanged(bool aHighlight) override;

      /**
       * A handler function that gets called whenever the hover status
       * of this tile changes.
       *
       * @param aHover Whether this tile is hovered.
       */
      void HandleHoverChanged(bool aHover) override;

    private:
      float mFadeValue;
      double mFadeSpeed;

      bool mFadingIn;
  };
}

#endif
