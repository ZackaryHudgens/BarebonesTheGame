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
       * Sets whether this tile should be highlighted.
       *
       * @param aHighlighted Whether this tile should be highlighted.
       */
      void SetHighlighted(bool aHighlighted);

      /**
       * Sets the color to use when highlighting this tile.
       *
       * @param aColor The color to use when highlighting this tile.
       */
      void SetHighlightColor(const glm::vec3& aColor) { mHighlightColor = aColor; }

      /**
       * Returns whether this tile is highlighted.
       *
       * @return Whether this tile is highlighted.
       */
      bool IsHighlighted() const { return mHighlighted; }

    protected:

      /**
       * A virtual function that gets called whenever the highlight status
       * changes.
       *
       * @param aHighlighted Whether this tile is being highlighted.
       */
      virtual void HandleHighlightChanged(bool aHighlighted) {}

      /**
       * Returns the highlight color.
       *
       * @return The highlight color.
       */
      glm::vec3 GetHighlightColor() const { return mHighlightColor; }

    private:
      glm::vec3 mHighlightColor;

      bool mHighlighted;
  };
}

#endif
