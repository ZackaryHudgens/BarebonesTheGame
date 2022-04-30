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
}

#endif
