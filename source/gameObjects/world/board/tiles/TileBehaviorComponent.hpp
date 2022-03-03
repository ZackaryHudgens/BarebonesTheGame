#ifndef TILEBEHAVIORCOMPONENT_HPP
#define TILEBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>
#include <Signal.hpp>

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
       * Sets whether the tile should be highlighted.
       *
       * @param aHighlight Whether the tile should be highlighted.
       */
      void SetHighlighted(bool aHighlight);

      /**
       * Sets the color to use when highlighting this tile.
       *
       * @param aColor The color to use when highlighting.
       */
      void SetHighlightColor(const glm::vec3& aColor);

      /**
       * Sets whether the tile is hovered over by the player.
       *
       * @param aHover Whether the tile is hovered over by the player.
       */
      void SetHovered(bool aHover);

    protected:

      /**
       * Returns whether this tile is highlighted.
       *
       * @return Whether this tile is highlighted.
       */
      bool IsHighlighted() const { return mHighlighted; }

      /**
       * Returns whether this tile is hovered.
       *
       * @return Whether this tile is hovered.
       */
      bool IsHovered() const { return mHovered; }

      /**
       * Returns the highlight color.
       *
       * @return The highlight color.
       */
      glm::vec3 GetHighlightColor() const { return mHighlightColor; }

      /**
       * Returns the hover color.
       *
       * @return The hover color.
       */
      glm::vec3 GetHoverColor() const { return mHoverColor; }

      /**
       * A virtual function that gets called whenever the highlight status
       * of this tile changes.
       *
       * @param aHighlight Whether this tile should be highlighted.
       */
      virtual void HandleHighlightChanged(bool aHighlight) {}

      /**
       * A virtual function that gets called whenever the hover status
       * of this tile changes.
       *
       * @param aHover Whether this tile is hovered.
       */
      virtual void HandleHoverChanged(bool aHover) {}

    private:
      glm::vec3 mHighlightColor;
      glm::vec3 mHoverColor;

      bool mHighlighted;
      bool mHovered;
  };

  typedef UrsineEngine::SignalT<UrsineEngine::GameObject&> TileReadyForUseSignal;
  extern TileReadyForUseSignal TileReadyForUse;
}

#endif
