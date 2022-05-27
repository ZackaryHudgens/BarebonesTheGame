#include "DefaultCharacterMover.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::DefaultCharacterMover;

/******************************************************************************/
Barebones::TileList DefaultCharacterMover::GetMovements(UrsineEngine::GameObject& aObject,
                                                        const TileLocation& aLocation) const
{
  TileList tiles;

  auto boardLayoutComponent = aObject.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    // Check tile to the right.
    TileLocation newMove(aLocation.first + 1, aLocation.second);
    if(boardLayoutComponent->GetTileAtLocation(newMove) != nullptr &&
       boardLayoutComponent->GetCharacterAtLocation(newMove) == nullptr)
    {
      tiles.emplace_back(newMove);
    }

    // Check tile to the left.
    newMove.first = aLocation.first - 1;
    if(boardLayoutComponent->GetTileAtLocation(newMove) != nullptr &&
       boardLayoutComponent->GetCharacterAtLocation(newMove) == nullptr)
    {
      tiles.emplace_back(newMove);
    }

    // Check tile above.
    newMove.first = aLocation.first;
    newMove.second = aLocation.second + 1;
    if(boardLayoutComponent->GetTileAtLocation(newMove) != nullptr &&
       boardLayoutComponent->GetCharacterAtLocation(newMove) == nullptr)
    {
      tiles.emplace_back(newMove);
    }

    // Check tile below.
    newMove.second = aLocation.second - 1;
    if(boardLayoutComponent->GetTileAtLocation(newMove) != nullptr &&
       boardLayoutComponent->GetCharacterAtLocation(newMove) == nullptr)
    {
      tiles.emplace_back(newMove);
    }
  }

  return tiles;
}
