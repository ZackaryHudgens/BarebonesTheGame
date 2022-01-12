#ifndef BOARDBEHAVIORCOMPONENT_HPP
#define BOARDBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

#include "CharacterBehaviorComponent.hpp"

namespace Barebones
{
  class BoardBehaviorComponent : public UrsineEngine::Component
  {
    public:

      /**
       * Constructor.
       */
      BoardBehaviorComponent();

      /**
       * When initializing, creates a number of TileObjects according to the
       * board's row and column count.
       */
      void Initialize() override;

      /**
       * Updates the board.
       */
      void Update() override;

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
       * Adds a GameObject to the board at the given position. If this
       * component is attached to a GameObject, the parent takes ownership
       * of the given object as a child object. If this component isn't
       * attached to a GameObject, this function returns false. This function
       * also returns false if the given coordinates are out of bounds.
       *
       * @param aObject The object to add.
       * @param aColumn The column to place the object in.
       * @param aRow The row to place the object in.
       * @return True if successful, false otherwise.
       */
      bool AddObjectAtPosition(std::unique_ptr<UrsineEngine::GameObject> aObject,
                               int aColumn,
                               int aRow);

      /**
       * Removes a GameObject at the given position.
       *
       * @param aColumn The column to remove an object from.
       * @param aRow The row to remove an object from.
       */
      void RemoveObjectAtPosition(int aColumn,
                                  int aRow);

      /**
       * Returns a pointer to the GameObject on the board at a given position.
       *
       * @param aColumn The column in question.
       * @param aRow The row in question.
       * @return A pointer to a GameObject, or nullptr if nothing is occupying
       *         the given space.
       */
      UrsineEngine::GameObject* GetObjectAtPosition(int aColumn,
                                                    int aRow);

    private:

      /**
       * A handler function that gets called whenever the selection
       * status of a character changes.
       *
       * @param aCharacter The character that was selected.
       */
      void HandleSelectionChanged(CharacterBehaviorComponent& aCharacter);

      std::vector<UrsineEngine::GameObject*> mTiles;
      std::vector<UrsineEngine::GameObject*> mCharacters;

      double mScaleTime;
      double mTileSpacing;

      int mColumns;
      int mRows;

      bool mInitialized;
  };
}

#endif
