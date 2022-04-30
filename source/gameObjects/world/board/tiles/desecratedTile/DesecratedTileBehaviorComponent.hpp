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
       * A virtual function that gets called whenever a character ends the turn
       * on this tile.
       *
       * @param aCharacter The character GameObject that ended the turn on this tile.
       */
      void HandleTurnEnded(UrsineEngine::GameObject& aCharacter) override;

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
