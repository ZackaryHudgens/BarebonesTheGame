#ifndef CHARACTERBEHAVIORCOMPONENT_HPP
#define CHARACTERBEHAVIORCOMPONENT_HPP

#include <map>

#include <Component.hpp>
#include <GameObject.hpp>

#include "BoardLayoutComponent.hpp"

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
       * Initializes the component.
       */
      void Initialize() override;

      /**
       * Updates the component.
       */
      void Update() override;

      /**
       * Moves the character to a position in world space at the given speed.
       *
       * @param aPosition The position to move to.
       * @param aSpeed The speed to move at.
       */
      void MoveToPosition(const glm::vec3& aPosition,
                          double aSpeed);

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
      virtual TileList GetMovements(UrsineEngine::GameObject& aObject,
                                    const TileLocation& aLocation) const;

    protected:

      /**
       * A virtual function that gets called during Update(). Should
       * be overridden by child classes.
       */
      virtual void ProtectedUpdate() {}

      /**
       * A virtual function that adds all skills for this character
       * to the parent GameObject. Note that the Move skill is added
       * to all characters by default in Initialize().
       *
       * Should be overridden by child classes.
       */
      virtual void AddSkills() {}

    private:
      glm::vec3 mTargetPosition;

      double mSpeed;

      bool mMoving;
  };
}

#endif
