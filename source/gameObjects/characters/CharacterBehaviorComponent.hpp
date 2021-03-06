#ifndef CHARACTERBEHAVIORCOMPONENT_HPP
#define CHARACTERBEHAVIORCOMPONENT_HPP

#include <map>
#include <queue>

#include <Component.hpp>
#include <GameObject.hpp>

#include "CharacterController.hpp"
#include "CharacterMover.hpp"
#include "CharacterState.hpp"

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
       * Sets the name for this type of character.
       *
       * @param aName The name for this type of character.
       */
      void SetName(const std::string& aName) { mName = aName; }

      /**
       * Returns the name of this character.
       *
       * @return The name of this character.
       */
      std::string GetName() const { return mName; }

      /**
       * Sets the type of this character.
       *
       * @param aType The new type of the character.
       */
      void SetType(const Type& aType) { mType = aType; }

      /**
       * Returns the type of this character.
       *
       * @return The type of this character.
       */
      Type GetType() const { return mType; }

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
       * Sets the speed of this character (the amount of distance the
       * character can cover in a single move).
       *
       * @param aSpeed The speed of this character.
       */
      void SetSpeed(int aSpeed) { mSpeed = aSpeed; }

      /**
       * Returns the speed of this character.
       *
       * @return The speed of this character.
       */
      int GetSpeed() const { return mSpeed; }

      /**
       * Sets the maximum health of this character. If the maximum health is
       * less than the current health, the current health is set equal to
       * the given value.
       *
       * @param aHealth The new maximum health of this character.
       */
      void SetMaximumHealth(int aHealth);

      /**
       * Returns this character's maximum health.
       *
       * @return This character's maximum health.
       */
      int GetMaximumHealth() const { return mMaximumHealth; }

      /**
       * Sets the current health of this character. If the new health value is
       * 0 or less, this character dies.
       *
       * @param aHealth The new current health of this character.
       */
      void SetCurrentHealth(int aHealth);

      /**
       * Returns this character's current health.
       *
       * @return This character's current health.
       */
      int GetCurrentHealth() const { return mCurrentHealth; }

      /**
       * Sets the mover for this character. The mover is used in determining
       * the shortest path list.
       *
       * @param aMover The new mover for this character.
       */
      void SetMover(std::unique_ptr<CharacterMover> aMover) { mMover.swap(aMover); }

      /**
       * Sets the controller for this character. The controller is used in
       * the TakeTurn() function.
       *
       * @param aController The new controller for this character.
       */
      void SetController(std::unique_ptr<CharacterController> aController) { mController.swap(aController); }

      /**
       * Adds a skill to this character.
       *
       * @param aSkill The skill to add.
       */
      void AddSkill(std::unique_ptr<Skill> aSkill);

      /**
       * Returns a pointer to this character's skill with the given name, or
       * nullptr if the character doesn't have a skill with the given name.
       *
       * @param aName The name of the skill to retrieve.
       * @return A pointer to the skill with the given name.
       */
      Skill* GetSkill(const std::string& aName);

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
       * Moves the character to a position in world space at the given speed.
       *
       * @param aPosition The position to move to.
       * @param aSpeed The speed to move at.
       */
      void MoveToPosition(const glm::vec3& aPosition,
                          double aSpeed);

      /**
       * Tells this character to take a turn on the given board. This function
       * uses the assigned CharacterController to control the character for a
       * turn. If no CharacterController has been set, this function does nothing.
       *
       * @param aBoard The board to take a turn on.
       */
      void TakeTurn(UrsineEngine::GameObject& aBoard);

      /**
       * Takes a damage value and applies it to this character's health.
       * The damage value is displayed as a status message.
       *
       * @param aValue The amount of damage to deal.
       */
      void DealDamage(int aValue);

      /**
       * Generates a list of shortest paths from a given starting tile
       * to each tile this character can move to on the given board.
       *
       * @param aBoard The board to generate shortest paths for.
       * @param aStartingLocation The location of the starting tile.
       * @return A list of shortest paths from the starting tile to each
       *         adjacent tile.
       */
      TilePathList GenerateShortestPathList(UrsineEngine::GameObject& aBoard,
                                            const TileLocation& aStartingLocation) const;

    private:

      // Pairs a string to display with a position to display it at.
      typedef std::pair<std::string, glm::vec3> StatusMessageInfo;

      /**
       * A function that generates a TileAdjacencyMap using this
       * character's GetMovements() function.
       *
       * @param aBoard The board to generate a map for.
       * @return A TileAdjacencyMap for the given board at the starting location.
       */
      TileAdjacencyMap GenerateAdjacencyMap(UrsineEngine::GameObject& aBoard) const;

      /**
       * Displays a message with the given text in front of the character.
       *
       * @param aInfo The status message to display.
       */
      void DisplayStatusMessage(const StatusMessageInfo& aInfo);

      std::unique_ptr<CharacterState> mMovementState;
      std::unique_ptr<CharacterState> mStatusState;

      std::unique_ptr<CharacterController> mController;
      std::unique_ptr<CharacterMover> mMover;

      std::vector<std::unique_ptr<Effect>> mEffects;
      std::vector<std::unique_ptr<Skill>> mSkills;

      std::queue<StatusMessageInfo> mStatusMessageQueue;
      double mStatusMessageWaitTime;
      double mLastStatusMessageCreatedTime;

      Side mSide;
      Type mType;

      std::string mName;

      int mSpeed;

      int mMaximumHealth;
      int mCurrentHealth;
  };
}

#endif
