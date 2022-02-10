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
       * Sets whether the tile should be highlighted and with what color.
       *
       * @param aHighlight Whether the tile should be highlighted.
       * @param aColor The color to use when highlighting this tile.
       */
      void SetHighlighted(bool aHighlight,
                          const glm::vec3& aColor = glm::vec3(1.0,
                                                              1.0,
                                                              1.0));

    protected:

      /**
       * A virtual function that gets called whenever the highlight status
       * of this tile changes.
       */
      virtual void HandleHighlightChanged() {}

      /**
       * Returns whether this tile is highlighted.
       *
       * @return Whether this tile is highlighted.
       */
      bool IsHighlighted() const { return mHighlighted; }

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
