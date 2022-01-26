#ifndef TILEBEHAVIORCOMPONENT_HPP
#define TILEBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <CoreSignals.hpp>

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
       * Sets whether this tile is being hovered over by the
       * player.
       *
       * @param aHovered Whether this tile is being hovered over by the player.
       */
      void SetHovered(bool aHovered);

      /**
       * Returns whether this tile is being hovered over.
       *
       * @return Whether this tile is being hovered over.
       */
      bool IsHovered() const { return mHovered; }

      /**
       * Sets whether this tile is highlighted to show a possible move.
       *
       * @param aHighlighted Whether this tile is highlighted.
       */
      void SetHighlighted(bool aHighlighted);

      /**
       * Returns whether this tile is being highlighted.
       *
       * @return Whether this tile is being highlighted.
       */
      bool IsHighlighted() const { return mHilighted; }

    protected:

      /**
       * A virtual function that gets called whenever the hover status
       * changes.
       *
       * @param aHovered Whether this tile is being hovered over.
       */
      virtual void HandleHoverChanged(bool aHovered) {}

      /**
       * A virtual function that gets called whenever the highlight status
       * changes.
       *
       * @param aHighlighted Whether this tile is being highlighted
       */
      virtual void HandleHighlightChanged(bool aHighlighted) {}

    private:
      bool mHovered;
      bool mHilighted;
  };

  typedef UrsineEngine::SignalT<TileBehaviorComponent&> TileHoveredSignal;
  extern TileHoveredSignal TileHovered;
}

#endif
