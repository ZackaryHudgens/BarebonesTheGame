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

  /**
   * Represents an edge in an undirected graph of tiles.
   */
  typedef std::pair<TileLocation, int> TileEdge;

  /**
   * Maps a tile location to a list of edges.
   */
  typedef std::pair<TileLocation, std::vector<TileEdge>> TileAdjacencyList;

  /**
   * Represents an undirected graph as a collection of adjacency lists.
   */
  typedef std::vector<TileAdjacencyList> TileAdjacencyGraph;
}

#endif
