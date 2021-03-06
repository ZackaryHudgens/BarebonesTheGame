#ifndef BOARDLAYOUTCOMPONENT_HPP
#define BOARDLAYOUTCOMPONENT_HPP

#include <Component.hpp>
#include <CoreSignals.hpp>
#include <GameObject.hpp>

#include "BoardState.hpp"

#include "TileFactory.hpp"
#include "TileUtil.hpp"

#include "CharacterBehaviorComponent.hpp"
#include "Skill.hpp"

namespace Barebones
{
  /**
   * The BoardLayoutComponent contains logic for creating and placing
   * tiles in world space, as well as maintaining a collection of
   * characters and what position they occupy on the board.
   */
  class BoardLayoutComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      BoardLayoutComponent();

      /**
       * When initializing, creates a number of TileObjects according to the
       * board's row and column count.
       */
      void Initialize() override;

      /**
       * Updates the component.
       *
       * @param aTime The time of the current Scene'e Update().
       */
      void Update(double aTime) override;

      /**
       * Returns the number of columns.
       *
       * @return The number of columns.
       */
      int GetColumns() const { return mColumns; }

      /**
       * Returns the number of rows.
       *
       * @return The number of rows.
       */
      int GetRows() const { return mRows; }

      /**
       * Adds a tile of the given type at at the given location on the board.
       * If the location is not within the board's boundaries, this function fails.
       * This function also fails if a tile already exists at the given location.
       *
       * @param aTileType The type of the new tile.
       * @param aLocation The location of the new tile.
       * @return True if successful, false otherwise.
       */
      bool AddTileAtLocation(const TileType& aTileType,
                             const TileLocation& aLocation);

      /**
       * Removes a tile from the board at the given location.
       *
       * @param aLocation The location of the tile to remove.
       */
      void RemoveTileAtLocation(const TileLocation& aLocation);

      /**
       * Adds a character to the board at the given location by taking
       * ownership of it and adding it as a child GameObject.
       *
       * @param aObject The character to add.
       * @param aLocation The location to add the character to.
       * @return True if successful, false otherwise.
       */
      bool AddCharacterAtLocation(std::unique_ptr<UrsineEngine::GameObject> aObject,
                                  const TileLocation& aLocation);

      /**
       * Removes a character at the given location.
       *
       * @param aLocation The location to remove a character from.
       */
      void RemoveCharacterAtLocation(const TileLocation& aLocation);

      /**
       * Focuses the board on the tile at the given location.
       *
       * @param aLocation The location of the newly focused tile.
       */
      void SetFocusedTileLocation(const TileLocation& aLocation);

      /**
       * Returns the location of the currently focused tile.
       *
       * @return The location of the currently focused tile.
       */
      TileLocation GetFocusedTileLocation() const { return mFocusedTileLocation; }

      /**
       * Returns a pointer to the tile on the board at a given location.
       *
       * @param aLocation The location to access.
       * @return A pointer to a GameObject, or nullptr if the given location
       *         is out of bounds.
       */
      UrsineEngine::GameObject* GetTileAtLocation(const TileLocation& aLocation);

      /**
       * Returns a pointer to the character on the board at a given location.
       *
       * @param aLocation The location to access.
       * @return A pointer to a GameObject, or nullptr if no character
       *         is occupying the given space.
       */
      UrsineEngine::GameObject* GetCharacterAtLocation(const TileLocation& aLocation);

      /**
       * Returns the location of the character with the given name, or
       * (-1, -1) if there is no character with the given name.
       *
       * @param aName The name of the GameObject for the desired character.
       * @return The location of the corresponding character, or (-1, -1)
       *         if no character was found.
       */
      TileLocation GetLocationOfCharacter(const std::string& aName);

      /**
       * Returns a vector of characters that are on the given side.
       *
       * @param aSide The side in question.
       */
      std::vector<UrsineEngine::GameObject*> GetCharactersOnSide(const Side& aSide);

      /**
       * Returns a vector of characters that are of the given type.
       *
       * @param aType The type of character.
       */
      std::vector<UrsineEngine::GameObject*> GetCharactersOfType(const Type& aType);

      /**
       * Moves a character at the given location along the given path.
       *
       * @param aCharacterLocation The location of the character.
       * @param aPath The path of tiles to follow.
       */
      void MoveCharacterAlongPath(const TileLocation& aCharacterLocation,
                                  const TileList& aPath);

    private:

      /**
       * Moves the followed character to the tile at the given location.
       *
       * @param aCurrentLocation The current location of the character.
       * @param aTargetLocation The location of the tile to move to.
       */
      void MoveCharacter(const TileLocation& aCurrentLocation,
                         const TileLocation& aTargetLocation);

      /**
       * A handler function that gets called whenever a player's turn begins.
       *
       * @param aPlayer The player whose turn began.
       */
      void HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer);

      /**
       * A handler function that gets called whenever a player's turn ends.
       *
       * @param aPlayer The player whose turn ended.
       */
      void HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer);

      /**
       * A handler function that gets called whenever a skill is selected
       * for use.
       *
       * @param aSkill The skill that was selected.
       */
      void HandleSkillSelected(Skill& aSkill);

      /**
       * A handler function that gets called whenever a skill is executed.
       *
       * @param aSkill The skill that was executed.
       */
      void HandleSkillExecuted(Skill& aSkill);

      /**
       * A handler function that gets called whenever the use of a skill
       * is cancelled.
       *
       * @param aSkill The skill that was cancelled.
       */
      void HandleSkillCancelled(Skill& aSkill);

      /**
       * A handler function that gets called whenever a character
       * finishes moving.
       *
       * @param aCharacter The character that finished moving.
       */
      void HandleCharacterFinishedMoving(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever a character dies.
       *
       * @param aCharacter The character that died.
       */
      void HandleCharacterDied(CharacterBehaviorComponent& aCharacter);

      /**
       * A handler function that gets called whenever the camera finishes
       * the initial panning sequence.
       *
       * @param aCamera The camera that finished panning.
       */
      void HandleCameraFinishedInitialSequence(UrsineEngine::GameObject& aCamera);

      /**
       * A handler function that gets called whenever a GameObject is about
       * to be deleted.
       *
       * @param aObject The GameObject that's about to be deleted.
       */
      void HandleObjectPendingDeletion(UrsineEngine::GameObject* aObject);

      std::unique_ptr<BoardState> mState;

      std::vector<std::vector<UrsineEngine::GameObject*>> mTiles;
      std::vector<std::vector<UrsineEngine::GameObject*>> mCharacters;

      UrsineEngine::GameObject* mMovingCharacter;
      TileList mFollowedPath;
      bool mWaitingForMovingCharacter;

      TileLocation mFocusedTileLocation;

      double mTileSpacing;
      int mColumns;
      int mRows;
  };
}

#endif
