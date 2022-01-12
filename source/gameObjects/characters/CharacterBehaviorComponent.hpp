#ifndef CHARACTERBEHAVIORCOMPONENT_HPP
#define CHARACTERBEHAVIORCOMPONENT_HPP

#include <map>

#include <Component.hpp>
#include <Signal.hpp>

namespace Barebones
{
  class CharacterBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      CharacterBehaviorComponent();

      /**
       * Returns the horizontal distance that this character can move.
       *
       * @return The horizontal distance that this character can move.
       */
      int GetHorizontalDistance() const { return mHorizontalDistance; }

      /**
       * Returns the vertical distance that this character can move.
       *
       * @return The vertical distance that this character can move.
       */
      int GetVerticalDistance() const { return mVerticalDistance; }

      /**
       * Returns the diagonal distance that this character can move.
       *
       * @return The diagonal distance that this character can move.
       */
      int GetDiagonalDistance() const { return mDiagonalDistance; }

      /**
       * Sets this character as either selected or deselected.
       *
       * @param aSelected Whether this character should be selected.
       */
      void SetSelected(bool aSelected);

      /**
       * Returns whether this character is selected.
       *
       * @return Whether this character is selected.
       */
      bool IsSelected() const { return mSelected; }

    private:

      /**
       * A virtual function that gets called whenever the selection
       * status of this character changes.
       *
       * @param aSelected Whether this character was selected.
       */
      virtual void HandleSelectionChanged(bool aSelected) {}

      int mHorizontalDistance;
      int mVerticalDistance;
      int mDiagonalDistance;

      bool mSelected;
  };

  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&> CharacterSelectedSignal;
  extern CharacterSelectedSignal CharacterSelected;
}

#endif
