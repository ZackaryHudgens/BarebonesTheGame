#ifndef BOARDOBJECT_HPP
#define BOARDOBJECT_HPP

#include <GameObject.hpp>

#include "TileObject.hpp"

namespace Barebones
{
  class BoardObject : public UrsineEngine::GameObject
  {
    public:

      /**
       * Constructor.
       */
      BoardObject(const std::string& aName);

      /**
       * Returns the number of rows on the board.
       *
       * @return The number of rows.
       */
      int GetRows() const { return mRows; }

      /**
       * Returns the number of columns on the board.
       *
       * @return The number of columns.
       */
      int GetColumns() const { return mColumns; }

    private:
      int mRows;
      int mColumns;
  };
}

#endif
