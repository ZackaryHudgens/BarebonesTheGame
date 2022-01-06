#ifndef BOARDBEHAVIORCOMPONENT_HPP
#define BOARDBEHAVIORCOMPONENT_HPP

#include <Component.hpp>
#include <GameObject.hpp>

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

    private:
      std::vector<std::vector<UrsineEngine::GameObject*>> mTileMap;

      double mScaleTime;

      int mColumns;
      int mRows;

      bool mInitialized;
  };
}

#endif
