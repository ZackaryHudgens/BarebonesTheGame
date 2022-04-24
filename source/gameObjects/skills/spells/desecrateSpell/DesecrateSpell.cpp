#include "DesecrateSpell.hpp"

#include <sstream>

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerBehaviorComponent.hpp"

#include "TileFactory.hpp"

using Barebones::DesecrateSpell;

/******************************************************************************/
DesecrateSpell::DesecrateSpell(UrsineEngine::GameObject& aParent)
  : Skill(aParent)
  , mRadius(2)
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
Barebones::TileList DesecrateSpell::GetValidTiles(UrsineEngine::GameObject& aBoard)
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
Barebones::TileList DesecrateSpell::GetTilesToHighlight(UrsineEngine::GameObject& aBoard)
{
  TileList tiles;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto humanPlayerBehaviorComponent = parent->GetFirstComponentOfType<HumanPlayerBehaviorComponent>();
    if(humanPlayerBehaviorComponent != nullptr)
    {
      auto playerLocation = humanPlayerBehaviorComponent->GetLocation();

      auto leftEdge = playerLocation.first - mRadius;
      auto rightEdge = playerLocation.first + mRadius;
      auto bottomEdge = playerLocation.second - mRadius;
      auto topEdge = playerLocation.second + mRadius;

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
    for(const auto& tileLocation : GetTilesToHighlight(aBoard))
    {
      // For each affected tile, create a new desecrated tile at that location.
      boardLayoutComponent->ChangeTileAtLocation(TileType::eDEFAULT, tileLocation);
    }
  }
}
