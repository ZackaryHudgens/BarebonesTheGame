#ifndef BOARDINPUTCOMPONENT_HPP
#define BOARDINPUTCOMPONENT_HPP

#include <Component.hpp>
#include <CoreSignals.hpp>

namespace Barebones
{
  class BoardInputComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      BoardInputComponent();

      /**
       * Loads the component.
       */
      void Load() override;

    private:

      /**
       * A handler function that gets called whenever the user presses
       * a key.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       */
      void HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                            int aMods);

      /**
       * Sets the hovered property of the tile at the given location
       * (if it exists) to true and un-hovers the tile at the
       * current location.
       *
       * @param aXPos The x position of the new location.
       * @param aYPos The y position of the new location.
       */
      void HoverOverTile(int aXPos,
                         int aYPos);

      int mPlayerXLocation;
      int mPlayerYLocation;
  };
}

#endif
