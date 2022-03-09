#ifndef CHARACTERBEHAVIORCOMPONENT_HPP
#define CHARACTERBEHAVIORCOMPONENT_HPP

#include <map>

#include <Component.hpp>
#include <GameObject.hpp>
#include <Signal.hpp>

#include "BoardLayoutComponent.hpp"

#include "Skill.hpp"

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
       * Returns a vector of this character's skills.
       *
       * @return This character's skills.
       */
      std::vector<Skill> GetSkills() const { return mSkills; }

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

      /**
       * Returns the maximum health value of this character.
       *
       * @return This character's maximum health.
       */
      int GetMaximumHealth() const { return mMaximumHealth; }

      /**
       * Returns the current health value of this character.
       *
       * @return This character's current health.
       */
      int GetCurrentHealth() const { return mCurrentHealth; }

    protected:

      /**
       * Adds a skill to this character.
       *
       * @param aSkill The skill to add.
       */
      void AddSkill(const Skill& aSkill);

      /**
       * Sets the maximum health of this character. If the maximum health is
       * less than the current health, the current health is set equal to
       * the given value.
       *
       * @param aHealth The new maximum health of this character.
       */
      void SetMaximumHealth(int aHealth);

      /**
       * Sets the current health of this character. If the new health value is
       * 0 or less, this character dies.
       *
       * @param aHealth The new current health of this character.
       */
      void SetCurrentHealth(int aHealth);

    private:
      glm::vec3 mTargetPosition;

      std::vector<Skill> mSkills;

      double mSpeed;

      int mMaximumHealth;
      int mCurrentHealth;

      bool mMoving;
  };

  typedef UrsineEngine::SignalT<CharacterBehaviorComponent&> CharacterDiedSignal;
  extern CharacterDiedSignal CharacterDied;
}

#endif
