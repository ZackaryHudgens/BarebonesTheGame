#ifndef TILEUTIL_HPP
#define TILEUTIL_HPP

#include <vector>

namespace Barebones
{
  /**
   * Represents a location on a 2D board. The first integer
   * corresponds to the column, and the second integer corresponds
   * to the row.
   */
  typedef std::pair<int, int> TileLocation;
  typedef std::vector<TileLocation> TileList;
}

#endif
