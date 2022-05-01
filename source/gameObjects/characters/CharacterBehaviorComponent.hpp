#ifndef CHARACTERBEHAVIORCOMPONENT_HPP
#define CHARACTERBEHAVIORCOMPONENT_HPP

#include <map>

#include <Component.hpp>
#include <GameObject.hpp>

#include "Effect.hpp"
#include "Side.hpp"
#include "Skill.hpp"

namespace Barebones
{
  enum class Type
  {
    eNONE,
    eHUMAN,
    eSKELETON
  };

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
       *
       * @param aTime The start time of the current Scene's Update()
       */
      void Update(double aTime) override;

      /**
       * Returns the name of this type of character.
       *
       * @return The name of this type of character.
       */
      std::string GetName() const { return mName; }

      /**
       * Moves the character to a position in world space at the given speed.
       * Optionally, the rebound flag can be set to move back to the original
       * position afterwards at the same speed.
       *
       * @param aPosition The position to move to.
       * @param aSpeed The speed to move at.
       * @param aRebound Whether to move back to the original position after
       *                 reaching the target position.
       */
      void MoveToPosition(const glm::vec3& aPosition,
                          double aSpeed,
                          bool aRebound = false);

      /**
       * Returns a vector of this character's skills.
       *
       * @return This character's skills.
       */
      std::vector<Skill*> GetSkills();

      /**
       * Adds a status effect to this character.
       *
       * @param aEffect The effect to add.
       */
      void AddEffect(std::unique_ptr<Effect> aEffect);

      /**
       * Removes the effect with the given name from this character.
       *
       * @param aEffectName The name of the effect to remove.
       */
      void RemoveEffect(const std::string& aName);

      /**
       * Returns a list of effects on this character.
       *
       * @return A list of effects on this character.
       */
      std::vector<Effect*> GetEffects();

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
       * Sets which side this character is on.
       *
       * @param aSide The new side for this character.
       */
      void SetSide(const Side& aSide) { mSide = aSide; }

      /**
       * Returns the side this character is on.
       *
       * @return The side for this character.
       */
      Side GetSide() const { return mSide; }

      /**
       * Returns the type of this character.
       *
       * @return The type of this character.
       */
      Type GetType() const { return mType; }

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

      /**
       * Takes a damage value and applies it to this character's health.
       * The damage value is displayed as a status message.
       *
       * @param aValue The amount of damage to deal.
       */
      void DealDamage(int aValue);

    protected:

      /**
       * A virtual function that gets called during Initialize().
       */
      virtual void ProtectedInitialize() {}

      /**
       * Sets the name for this type of character.
       *
       * @param aName The name for this type of character.
       */
      void SetName(const std::string& aName) { mName = aName; }

      /**
       * Sets the type of this character.
       *
       * @param aType The new type of the character.
       */
      void SetType(const Type& aType) { mType = aType; }

      /**
       * Adds a skill to this character.
       *
       * @param aSkill The skill to add.
       */
      void AddSkill(std::unique_ptr<Skill> aSkill);

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

      /**
       * Displays a message with the given text in front of and above
       * the character.
       *
       * @param aText The text to display.
       */
      void DisplayStatusMessage(const std::string& aText);

      glm::vec3 mTargetPosition;
      glm::vec3 mOriginalPosition;

      double mFadeValue;
      double mFadeSpeed;

      std::vector<std::unique_ptr<Effect>> mEffects;
      std::vector<std::unique_ptr<Skill>> mSkills;

      Side mSide;
      Type mType;

      std::string mName;

      double mSpeed;

      int mMaximumHealth;
      int mCurrentHealth;

      bool mMoving;
      bool mRebound;
      bool mDying;
  };
}

#endif
