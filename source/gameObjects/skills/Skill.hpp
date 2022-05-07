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
       * Executes this skill.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      void Execute(UrsineEngine::GameObject& aBoard,
                   const TileLocation& aLocation);

      /**
       * Enables or disables this skill.
       *
       * @param aEnabled Whether to enable or disable this skill.
       */
      void SetEnabled(bool aEnabled) { mEnabled = aEnabled; }

      /**
       * Returns whether this skill is enabled.
       *
       * @return Whether this skill is enabled.
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
       * A virtual function that gets called during Execute().
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location on the board to execute this skill.
       */
      virtual void ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                    const TileLocation& aLocation) = 0;

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
