#include "DiagonalCharacterMover.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::DiagonalCharacterMover;

/******************************************************************************/
Barebones::TileList DiagonalCharacterMover::GetMovements(UrsineEngine::GameObject& aObject,
                                                         const TileLocation& aLocation) const
{
  TileList tiles;

  auto boardLayoutComponent = aObject.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    TileLocation newMove(aLocation.first + 1, aLocation.second + 1);
    if(boardLayoutComponent->GetTileAtLocation(newMove) != nullptr &&
       boardLayoutComponent->GetCharacterAtLocation(newMove) == nullptr)
    {
      tiles.emplace_back(newMove);
    }

    newMove.first = aLocation.first - 1;
    newMove.second = aLocation.second - 1;
    if(boardLayoutComponent->GetTileAtLocation(newMove) != nullptr &&
       boardLayoutComponent->GetCharacterAtLocation(newMove) == nullptr)
    {
      tiles.emplace_back(newMove);
    }

    newMove.first = aLocation.first + 1;
    newMove.second = aLocation.second - 1;
    if(boardLayoutComponent->GetTileAtLocation(newMove) != nullptr &&
       boardLayoutComponent->GetCharacterAtLocation(newMove) == nullptr)
    {
      tiles.emplace_back(newMove);
    }

    newMove.first = aLocation.first - 1;
    newMove.second = aLocation.second + 1;
    if(boardLayoutComponent->GetTileAtLocation(newMove) != nullptr &&
       boardLayoutComponent->GetCharacterAtLocation(newMove) == nullptr)
    {
      tiles.emplace_back(newMove);
    }
  }

  return tiles;
}
