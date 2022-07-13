#ifndef SKILL_HPP
#define SKILL_HPP

#include <GameObject.hpp>
#include <Observer.hpp>

#include "SkillAction.hpp"

#include "TileUtil.hpp"

#include "VisualEffectFactory.hpp"

namespace Barebones
{
  class Skill
  {
    public:

      /**
       * Constructor.
       */
      Skill();
      virtual ~Skill() {};

      /**
       * Sets the character that owns this skill.
       *
       * @param aCharacter The new owning character of this skill.
       */
      void SetCharacter(UrsineEngine::GameObject& aCharacter) { mCharacter = &aCharacter; }

      /**
       * Sets the name of the skill.
       *
       * @param aName The name of the skill.
       */
      void SetName(const std::string& aName) { mName = aName; }

      /**
       * Returns the name of the skill.
       *
       * @return The name of the skill.
       */
      std::string GetName() const { return mName; }

      /**
       * Sets the fluff description of the skill. The fluff description
       * is basically flavor text; it doesn't tell the player any
       * practical information. An example could be "Hurls a bone at the
       * target."
       *
       * @param aDescription The fluff description of the skill.
       */
      void SetFluffDescription(const std::string& aDescription) { mFluffDescription = aDescription; }

      /**
       * Returns the description of the skill, which is a combination of the
       * fluff description and all the descriptions of the actions this skill
       * possesses.
       *
       * @return The description of the skill.
       */
      std::string GetDescription() const;

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
       * Adds an action to shis skill. Actions are executed during Execute()
       * and define what this skill does.
       *
       * @param aAction The action to add.
       */
      void AddAction(std::unique_ptr<SkillAction> aAction);

      /**
       * Returns a vector of actions of the given type.
       *
       * @return A vector of actions of the given type.
       */
      template<typename T>
      std::vector<T*> GetActionsOfType() const
      {
        std::vector<T*> actions;

        for(const auto& action : mActions)
        {
          auto actionAsType = dynamic_cast<T*>(action.get());
          if(actionAsType != nullptr)
          {
            actions.emplace_back(actionAsType);
          }
        }

        return actions;
      }

      /**
       * Returns the first action of the given type. Useful if the caller knows
       * that this skill only has one action of the given type.
       *
       * @return A pointer to the first action of the given type, or nullptr
       *         if no action of the given type exists.
       */
      template<typename T>
      T* GetFirstActionOfType() const
      {
        T* actionOfType = nullptr;

        for(const auto& action : mActions)
        {
          auto actionAsType = dynamic_cast<T*>(action.get());
          if(actionAsType != nullptr)
          {
            actionOfType = actionAsType;
            break;
          }
        }

        return actionOfType;
      }

      /**
       * Adds a visual effect type to this skill. During Execute(), this skill
       * will create a visual effect object of each type added through this
       * function.
       *
       * @param aType The type of visual effect to add.
       */
      void AddVisualEffect(const VisualEffectType& aType) { mVisualEffects.emplace_back(aType); }

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
       * location of the owning GameObject on the given board as
       * the source location.
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
       * Returns the owning character GameObject.
       *
       * @return The character GameObject that owns this skill.
       */
      UrsineEngine::GameObject* GetCharacter() { return mCharacter; }

      /**
       * Returns the location of the owning character on the given board.
       *
       * @param aBoard The board to calculate character location for.
       */
      TileLocation GetCharacterLocation(UrsineEngine::GameObject& aBoard);

      /**
       * Checks if the given location on the given board has an enemy.
       *
       * @param aBoard The board to check.
       * @param aLocation The location on the board to check.
       * @return True if there is an enemy, false otherwise.
       */
      bool IsEnemyAtLocation(UrsineEngine::GameObject& aBoard,
                             const TileLocation& aLocation);

    private:

      /**
       * Deals damage to the character at the given location, then calls
       * ProtectedExecute() for custom behavior.
       *
       * @param aBoard The board to execute this skill on.
       * @param aLocation The location to execute this skill on.
       */
      void PrivateExecute(UrsineEngine::GameObject& aBoard,
                          const TileLocation& aLocation);

      /**
       * A handler function that gets executed whenever a visual effect
       * GameObject finishes its animation, movement, etc.
       *
       * @param aVisualEffect The visual effect GameObject.
       */
      void HandleSkillVisualEffectFinished(UrsineEngine::GameObject& aVisualEffect);

      std::vector<std::unique_ptr<SkillAction>> mActions;
      std::vector<VisualEffectType> mVisualEffects;
      std::vector<UrsineEngine::GameObject*> mActiveVisualEffects;

      UrsineEngine::GameObject* mCharacter;

      UrsineEngine::GameObject* mBoard;
      TileLocation mExecuteLocation;

      UrsineEngine::Observer mObserver;

      std::string mName;
      std::string mFluffDescription;

      bool mEnabled;
  };
}

#endif
