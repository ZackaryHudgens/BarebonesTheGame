#ifndef BOARDINPUTCOMPONENT_HPP
#define BOARDINPUTCOMPONENT_HPP

#include <Component.hpp>
#include <CoreSignals.hpp>

#include "BoardInputState.hpp"
#include "BoardLayoutComponent.hpp"

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

      /**
       * Enables or disables this component. While disabled, this component
       * won't process any input events.
       *
       * @param aEnabled Whether to enable this component.
       */
      void SetEnabled(bool aEnabled) { mEnabled = aEnabled; }

      /**
       * Sets the player's location on the board. Note that this may be overridden
       * by the input state.
       *
       * @param aLocation The new location of the player on the board.
       */
      void SetPlayerLocation(const TileLocation& aLocation);

      /**
       * Returns the player's location on the board. The first integer
       * corresponds to the column and the second integer corresponds to
       * the row.
       *
       * @return The location of the player on the board.
       */
      TileLocation GetPlayerLocation() const { return mPlayerLocation; }

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
       * A handler function that gets called whenever the user holds
       * a key down long enough to repeat the input.
       *
       * @param aCode The KeyCode for the key that was pressed.
       * @param aMods Any modifiers present when the key was pressed.
       * @return A pointer to a new state if this key caused the input
       *         to move to a new state, otherwise nullptr.
       */
      void HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                             int aMods);

      /**
       * A handler function that gets called whenever the user
       * selects a skill to use from a menu.
       *
       * @param aObject The skill object that was selected.
       */
      void HandleSkillSelected(UrsineEngine::GameObject* aObject);

      std::unique_ptr<BoardInputState> mState;

      TileLocation mPlayerLocation;

      bool mEnabled;
  };

  typedef UrsineEngine::SignalT<const TileLocation&> PlayerMovedSignal;
  extern PlayerMovedSignal PlayerMoved;
}

#endif
