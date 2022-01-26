#ifndef CHARACTERBEHAVIORCOMPONENT_HPP
#define CHARACTERBEHAVIORCOMPONENT_HPP

#include <map>

#include <Component.hpp>
#include <GameObject.hpp>
#include <Signal.hpp>

namespace Barebones
{
  typedef std::pair<int, int> TileLocation;
  typedef std::vector<TileLocation> MoveList;

  class CharacterBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      CharacterBehaviorComponent();

      /**
       * Updates the component.
       */
      void Update() override;

      /**
       * Moves the character to a location in world space at the given speed.
       *
       * @param aPosition The position to move to.
       * @param aSpeed The speed to move at.
       */
      void MoveCharacter(const glm::vec3& aPosition,
                         double aSpeed);

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
       * @param aObject A GameObject containing a BoardLoyoutComponent.
       * @param aLocation The initial location.
       * @return A list of possible movements.
       */
      virtual MoveList GetMovements(UrsineEngine::GameObject& aObject,
                                    const TileLocation& aLocation) const;

    protected:

      /**
       * A virtual function that gets called during Update(). Should
       * be overridden by child classes.
       */
      virtual void ProtectedUpdate() {}


    private:

      /**
       * A virtual function that gets called whenever the selection
       * status of this character changes.
       *
       * @param aSelected Whether this character was selected.
       */
      virtual void HandleSelectionChanged(bool aSelected) {}

      glm::vec3 mTargetPosition;

      double mSpeed;

      bool mMoving;
      bool mSelected;
  };

  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&> CharacterSelectedSignal;
  extern CharacterSelectedSignal CharacterSelected;
}

#endif
