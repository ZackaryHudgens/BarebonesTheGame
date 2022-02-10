#ifndef BASICSKELETONBEHAVIORCOMPONENT_HPP
#define BASICSKELETONBEHAVIORCOMPONENT_HPP

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
  class BasicSkeletonBehaviorComponent : public CharacterBehaviorComponent
  {
    public:

      /**
       * Constructor.
       */
      BasicSkeletonBehaviorComponent();

      /**
       * Returns a list of possible movements given a location on a board.
       * The first integer of each pair corresponds to the column;
       * the second integer corresponds to the row.
       *
       * @param aObject A GameObject containing a BoardLoyoutComponent.
       * @param aLocation The location to move from.
       * @return A list of possible movements.
       */
      TileList GetMovements(UrsineEngine::GameObject& aObject,
                            const TileLocation& aLocation) const override;

    protected:

      /**
       * Updates the component.
       */
      void ProtectedUpdate() override;

    private:

      /**
       * A handler function that gets called whenever the selection
       * status of this character changes.
       *
       * @param aSelected Whether this character was selected.
       */
      void HandleSelectionChanged(bool aSelected) override;

      double mGlowSpeed;
      double mTimeBeganGlowing;

      int mHorizontalMovement;
      int mVerticalMovement;
  };
}

#endif
