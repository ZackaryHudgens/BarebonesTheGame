#ifndef CHARACTERBEHAVIORCOMPONENT_HPP
#define CHARACTERBEHAVIORCOMPONENT_HPP

#include <map>

#include <Component.hpp>
#include <Signal.hpp>

namespace Barebones
{
  typedef std::pair<int, int> TileLocation;
  typedef std::vector<std::pair<int, int>> MoveList;

  class CharacterBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      CharacterBehaviorComponent();

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

      /**
       * A virtual function that returns a list of possible movements
       * given a location on a board. The first integer of each
       * pair corresponds to the column; the second integer corresponds
       * to the row.
       *
       * @param aLocation The location to move from.
       * @return A list of possible movements.
       */
      virtual MoveList GetMovements(const TileLocation& aLocation) const;

    private:

      /**
       * A virtual function that gets called whenever the selection
       * status of this character changes.
       *
       * @param aSelected Whether this character was selected.
       */
      virtual void HandleSelectionChanged(bool aSelected) {}

      bool mSelected;
  };

  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&> CharacterSelectedSignal;
  extern CharacterSelectedSignal CharacterSelected;
}

#endif
