#ifndef SKILL_HPP
#define SKILL_HPP

#include <GameObject.hpp>

#include "TileUtil.hpp"

namespace Barebones
{
  class Skill
  {
    public:

      /**
       * Constructor.
       *
       * @param aParent The GameObject that owns this skill.
       */
      Skill(UrsineEngine::GameObject& aParent);

      /**
       * Selects this skill for use, but doesn't execute it.
       */
      void Select();

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
       * for executing this skill.
       *
       * @param aBoard The board GameObject to use this skill on.
       */
      virtual TileList GetValidTiles(UrsineEngine::GameObject& aBoard) { return TileList(); }

      /**
       * Returns true if the given tile location on the given board
       * is valid for executing this skill. This function uses the virtual
       * GetValidTiles() function.
       *
       * @param aBoard The board GameObject to use this skill on.
       * @param aLocation The TileLocation to use this skill on.
       * @return True if the TileLocation is valid, false otherwise.
       */
      bool IsTileValid(UrsineEngine::GameObject& aBoard,
                       const TileLocation& aLocation);

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
       */
      virtual TileList GetTilesToHighlight(UrsineEngine::GameObject& aBoard) { return GetValidTiles(aBoard); }

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

    protected:

      /**
       * A virtual function that gets called during Select().
       *
       * This can be overridden to perform an action when the user selects
       * this skill from a menu.
       */
      virtual void ProtectedSelect() {}

      /**
       * A virtual function that gets called during Execute().
       *
       * This must be overridden to perform some action when the user
       * chooses to execute this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      virtual void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                    const TileLocation& aLocation) = 0;

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
       * Returns the parent that owns this skill.
       *
       * @return The parent that owns this skill.
       */
      UrsineEngine::GameObject* GetParent() { return mParent; }

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

    private:
      UrsineEngine::GameObject* mParent;

      std::string mDescription;
      std::string mName;

      bool mEnabled;
  };
}

#endif
