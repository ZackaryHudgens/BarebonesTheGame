#ifndef TILEUTIL_HPP
#define TILEUTIL_HPP

#include <map>
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

  /**
   * Represents an edge between tiles in an undirected graph.
   * The first member is the TileLocation at the end of the edge,
   * and the second member is the cost associated with traveling
   * to it.
   */
  typedef std::pair<TileLocation, int> TileEdge;

  /**
   * Maps a tile's location to a list of adjacent tiles.
   */
  typedef std::map<TileLocation, std::vector<TileEdge>> TileAdjacencyMap;

  /**
   * Pairs a list of tiles with the cost of traversing those tiles.
   */
  typedef std::pair<TileList, int> TilePath;
  typedef std::vector<TilePath> TilePathList;
}

#endif
