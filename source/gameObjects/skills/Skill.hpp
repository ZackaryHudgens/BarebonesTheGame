#ifndef SKILL_HPP
#define SKILL_HPP

#include <GameObject.hpp>
#include <Observer.hpp>

#include "TileUtil.hpp"

namespace Barebones
{
  class Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aCharacter The character GameObject that owns this skill.
       */
      Skill(UrsineEngine::GameObject& aCharacter);

      /**
       * Returns the name of the skill.
       *
       * @return The name of the skill.
       */
      std::string GetName() const { return mName; }

      /**
       * Returns the description of the skill.
       *
       * @return The description of the skill.
       */
      std::string GetDescription() const { return mDescription; }

      /**
       * Returns the damage this skill deals.
       *
       * @return This skill's damage.
       */
      int GetDamage() const { return mDamage; }

      /**
       * Selects this skill for use, but doesn't execute it.
       *
       * @param aBoard The board to execute this skill on in the future.
       */
      void Select(UrsineEngine::GameObject& aBoard);

      /**
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void Execute(UrsineEngine::GameObject& aBoard,
                   const TileLocation& aLocation);

      /**
       * Cancels the usage of this skill.
       */
      void Cancel();

      /**
       * Enables or disables this skill. Disabled skills can't be used.
       *
       * @param aEnabled Whether to enable or disable this skill.
       */
      void SetEnabled(bool aEnabled);

      /**
       * Returns whether this skill is enabled.
       *
       * @return True if this skill is enabled, false if it's disabled.
       */
      bool IsEnabled() const { return mEnabled; }

      /**
       * A virtual function that returns a vector of valid tile locations
       * for executing this skill from a given location.
       *
       * Alternatively, if no location is given, the skill will use the
       * location of the owning GameObject on the given board.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get valid tiles for.
       */
      virtual TileList GetValidTiles(UrsineEngine::GameObject& aBoard,
                                     const TileLocation& aSourceLocation) { return TileList(); }
      TileList GetValidTiles(UrsineEngine::GameObject& aBoard);

      /**
       * Returns true if the given tile location on the given board
       * is valid for executing this skill. This function uses the virtual
       * GetValidTiles() function to determine validity.
       *
       * If no source location is given, the skill will use the
       * location of the owning GameObject on the given board.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get valid tiles for.
       * @param aTargetLocation The location to check validity of.
       * @return True if aTargetLocation is in the valid tiles list,
       *         false otherwise.
       */
      bool IsTileValid(UrsineEngine::GameObject& aBoard,
                       const TileLocation& aSourceLocation,
                       const TileLocation& aTargetLocation);
      bool IsTileValid(UrsineEngine::GameObject& aBoard,
                       const TileLocation& aTargetLocation);

      /**
       * A virtual function that returns a vector of tiles that are affected
       * by this skill at a given location. This function is called during
       * Execute() to determine which tiles to perform an action on.
       *
       * By default, the only affected tile is the given one.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get affected tiles for.
       */
      virtual TileList GetAffectedTiles(UrsineEngine::GameObject& aBoard,
                                        const TileLocation& aSourceLocation);

      /**
       * A virtual function that returns a vector of tiles to highlight when
       * the player selects this skill but before executing it. This is
       * different from GetValidTiles() in that a skill might have an
       * area-of-effect that should be communicated to the player, but not
       * all of the affected tiles are valid for execution.
       *
       * By default, all valid tiles are highlighted.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aSourceLocation The location to get highlighted tiles for.
       */
      virtual TileList GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                           const TileLocation& aSourceLocation) { return GetValidTiles(aBoard, aSourceLocation); }

    protected:

      /**
       * A virtual function that gets called during Select().
       *
       * This can be overridden to perform an action when the user selects
       * this skill from a menu.
       *
       * @param aBoard The board to execute this skill on in the future.
       */
      virtual void ProtectedSelect(UrsineEngine::GameObject& aBoard) {}

      /**
       * A virtual function that gets called during Execute().
       *
       * This can be overridden to perform some action when the user
       * chooses to execute this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      virtual void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                    const TileLocation& aLocation) {};

      /**
       * A virtual function that gets called during Cancel().
       *
       * This can be overridden to perform an action when the user cancels
       * the usage of this skill.
       */
      virtual void ProtectedCancel() {}

      /**
       * A virtual function that gets called during SetEnabled().
       *
       * @param aEnabled Whether this skill was enabled or disabled.
       */
      virtual void HandleEnabledChanged(bool aEnabled) {}

      /**
       * A virtual function that gets called during Execute(). This returns
       * a GameObject that contains some logic for displaying a sprite or
       * other visual effect, and then deletes itself. When the object deletes
       * itself, damage is dealt and ProtectedExecute() is called.
       *
       * If no visual effect is created, the skill is executed immediately.
       *
       * @param aBoard The board to create a visual effect on.
       * @param aLocation The location to create a visual effect at.
       * @return A GameObject that represents any visual effect for this skill.
       */
      virtual std::unique_ptr<UrsineEngine::GameObject> CreateVisualEffect(UrsineEngine::GameObject& aBoard,
                                                                           const TileLocation& aLocation) { return nullptr; }

      /**
       * Returns the owning character GameObject.
       *
       * @return The character GameObject that owns this skill.
       */
      UrsineEngine::GameObject* GetCharacter() { return mCharacter; }

      /**
       * A handler function that gets called whenever a GameObject is
       * about to be deleted. If the object is the visual effect this
       * skill is waiting on, this skill is then executed.
       *
       * @param aObject The GameObject about to be deleted.
       */
      void HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject);

      /**
       * Checks if the given location on the given board has an enemy.
       *
       * @param aBoard The board to check.
       * @param aLocation The location on the board to check.
       * @return True if there is an enemy, false otherwise.
       */
      bool IsEnemyAtLocation(UrsineEngine::GameObject& aBoard,
                             const TileLocation& aLocation);

      /**
       * Sets the name of the skill.
       *
       * @param aName The name of the skill.
       */
      void SetName(const std::string& aName) { mName = aName; }

      /**
       * Sets the description of the skill.
       *
       * @param aDescription The description of the skill.
       */
      void SetDescription(const std::string& aDescription) { mDescription = aDescription; }

      /**
       * Sets the damage this skill deals.
       *
       * @param aDamage The damage of this skill.
       */
      void SetDamage(int aDamage) { mDamage = aDamage; }

    private:
      UrsineEngine::GameObject* mCharacter;
      UrsineEngine::GameObject* mVisualEffect;

      UrsineEngine::GameObject* mBoard;
      TileLocation mExecuteLocation;

      UrsineEngine::Observer mObserver;

      std::string mDescription;
      std::string mName;

      int mDamage;

      bool mEnabled;
  };
}

#endif
