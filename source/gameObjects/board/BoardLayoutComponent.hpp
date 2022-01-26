#ifndef BOARDLAYOUTCOMPONENT_HPP
#define BOARDLAYOUTCOMPONENT_HPP

#include <Component.hpp>
#include <CoreSignals.hpp>
#include <GameObject.hpp>

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
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
       * Returns the number of rows on the board.
       *
       * @return The number of rows on the board.
       */
      int GetRows() const { return mRows; }

      /**
       * Returns the number of columns on the board.
       *
       * @return The number of columns on the board.
       */
      int GetColumns() const { return mColumns; }

      /**
       * Returns the amount of empty space between tiles.
       *
       * @return The spacing between tiles.
       */
      double GetTileSpacing() const { return mTileSpacing; }

      /**
       * Adds a character to the board at the given position.
       *
       * If this component is attached to a GameObject, the parent
       * takes ownership of the given object as a child object.
       * If this component isn't attached to a GameObject, this
       * function returns false. This function also returns false
       * if the given coordinates are out of bounds.
       *
       * @param aObject The character to add.
       * @param aColumn The column to place the object in.
       * @param aRow The row to place the object in.
       * @return True if successful, false otherwise.
       */
      bool AddCharacterAtPosition(std::unique_ptr<UrsineEngine::GameObject> aObject,
                                  int aColumn,
                                  int aRow);

      /**
       * Removes a character at the given position.
       *
       * @param aColumn The column to remove an object from.
       * @param aRow The row to remove an object from.
       */
      void RemoveCharacterAtPosition(int aColumn,
                                     int aRow);

      /**
       * Returns a pointer to the tile on the board at a given position.
       *
       * @param aColumn The column to access.
       * @param aRow The row to access.
       * @return A pointer to a GameObject, or nullptr if the given position
       *         is out of bounds.
       */
      UrsineEngine::GameObject* GetTileAtPosition(int aColumn,
                                                  int aRow);

      /**
       * Returns a pointer to the character on the board at a given position.
       *
       * @param aColumn The column to access.
       * @param aRow The row to access.
       * @return A pointer to a GameObject, or nullptr if no character
       *         is occupying the given space.
       */
      UrsineEngine::GameObject* GetCharacterAtPosition(int aColumn,
                                                       int aRow);

      /**
       * Moves the currently selected character to the given position.
       *
       * @param aColumn The column to move to.
       * @param aRow The row to move to.
       */
      void MoveSelectedCharacter(int aColumn,
                                 int aRow);

      /**
       * Returns the currently selected character.
       *
       * @return A pointer the currently selected character, or nullptr
       *         if no character is selected.
       */
      UrsineEngine::GameObject* GetSelectedCharacter() { return mSelectedCharacter; }

    private:

      /**
       * A handler function that gets called whenever the selection
       * status of a character changes.
       *
       * @param aCharacter The character that was selected.
       */
      void HandleSelectionChanged(CharacterBehaviorComponent& aCharacter);

      std::vector<std::vector<UrsineEngine::GameObject*>> mTiles;
      std::vector<std::vector<UrsineEngine::GameObject*>> mCharacters;

      UrsineEngine::GameObject* mSelectedCharacter;

      double mTileSpacing;

      int mColumns;
      int mRows;
  };
}

#endif
