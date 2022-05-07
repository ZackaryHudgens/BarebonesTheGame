#include "EnemyBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "Signals.hpp"

using Barebones::EnemyBehaviorComponent;

/******************************************************************************/
EnemyBehaviorComponent::EnemyBehaviorComponent()
  : CharacterBehaviorComponent()
{
}

/******************************************************************************/
void EnemyBehaviorComponent::EndTurn()
{
  CharacterTurnEnded.Notify(*this);
}

/******************************************************************************/
int EnemyBehaviorComponent::CalculateCostofMovement(const TileLocation& aInitialLocation,
                                                    const TileLocation& aTargetLocation) const
{
  return 1;
}

/******************************************************************************/
Barebones::TileAdjacencyGraph EnemyBehaviorComponent::GenerateGraph(UrsineEngine::GameObject& aBoard) const
{
  TileAdjacencyGraph graph;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto columns = boardLayoutComponent->GetColumns();
    auto rows = boardLayoutComponent->GetRows();

    // For each tile, generate a TileAdjacencyList. A tile is considered
    // adjacent to another tile if the second tile is a valid movement
    // for this character from the first tile.
    for(int c = 0; c < columns; ++c)
    {
      for(int r = 0; r < rows; ++r)
      {
        TileLocation currentLocation(c, r);
        auto neighbors = GetMovements(aBoard, currentLocation);

        TileAdjacencyList adjacentTiles;
        adjacentTiles.first = currentLocation;

        // Create an edge for each valid movement.
        std::vector<TileEdge> edges;
        for(auto& neighborLocation : neighbors)
        {
          TileEdge edge(neighborLocation, CalculateCostofMovement(currentLocation,
                                                                  neighborLocation));
          edges.emplace_back(edge);
        }

        // Add these edges to the list of adjacent tiles.
        adjacentTiles.second = edges;

        // Add the list to the graph.
        graph.emplace_back(adjacentTiles);
      }
    }
  }

  return graph;
}
