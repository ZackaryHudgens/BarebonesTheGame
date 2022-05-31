#include "DesecrateSpell.hpp"

#include <sstream>

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerBehaviorComponent.hpp"

#include "TileFactory.hpp"

using Barebones::DesecrateSpell;

/******************************************************************************/
DesecrateSpell::DesecrateSpell(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
  , mRadius(1)
{
  SetName("Desecrate");

  std::stringstream ss;
  ss << "Desecrates all tiles\nwithin ";
  ss << mRadius;
  ss << " spaces\nof the target tile.\n\n";
  ss << "Desecrated tiles\ndamage enemies and\nheal skeletons.";
  SetDescription(ss.str());
}

/******************************************************************************/
Barebones::TileList DesecrateSpell::GetValidTiles(UrsineEngine::GameObject& aBoard,
                                                  const TileLocation& aSourceLocation)
{
  TileList tiles;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    TileLocation tileLocation;

    // All tiles are valid for executing this skill.
    for(int c = 0; c < boardLayoutComponent->GetColumns(); ++c)
    {
      tileLocation.first = c;
      for(int r = 0; r < boardLayoutComponent->GetRows(); ++r)
      {
        tileLocation.second = r;
        tiles.emplace_back(tileLocation);
      }
    }
  }

  return tiles;
}

/******************************************************************************/
Barebones::TileList DesecrateSpell::GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                                        const TileLocation& aSourceLocation)
{
  TileList tiles;

  auto leftEdge = aSourceLocation.first - mRadius;
  auto rightEdge = aSourceLocation.first + mRadius;
  auto bottomEdge = aSourceLocation.second - mRadius;
  auto topEdge = aSourceLocation.second + mRadius;

  for(int column = leftEdge; column <= rightEdge; ++column)
  {
    for(int row = bottomEdge; row <= topEdge; ++row)
    {
      TileLocation affectedTile;
      affectedTile.first = column;
      affectedTile.second = row;
      tiles.emplace_back(affectedTile);
    }
  }

  return tiles;
}

/******************************************************************************/
void DesecrateSpell::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                      const TileLocation& aLocation)
{
  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    for(const auto& tileLocation : GetTilesToHighlight(aBoard, aLocation))
    {
      // For each affected tile, create a new desecrated tile at that location.
      boardLayoutComponent->RemoveTileAtLocation(tileLocation);
      boardLayoutComponent->AddTileAtLocation(TileType::eDESECRATED, tileLocation);
    }
  }
}
