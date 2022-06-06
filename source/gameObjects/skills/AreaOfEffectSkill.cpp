#include "AreaOfEffectSkill.hpp"

#include "BoardLayoutComponent.hpp"

using Barebones::AreaOfEffectSkill;

/******************************************************************************/
AreaOfEffectSkill::AreaOfEffectSkill(UrsineEngine::GameObject& aCharacter, int aRadius)
  : Skill(aCharacter)
  , mRadius(aRadius)
{
}

/******************************************************************************/
Barebones::TileList AreaOfEffectSkill::GetValidTiles(UrsineEngine::GameObject& aBoard,
                                                     const TileLocation& aSourceLocation)
{
  TileList tiles;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    // All tiles are valid for executing AoE skills.
    auto columns = boardLayoutComponent->GetColumns();
    auto rows = boardLayoutComponent->GetRows();

    for(int c = 0; c < columns; ++c)
    {
      for(int r = 0; r < rows; ++r)
      {
        tiles.emplace_back(TileLocation(c, r));
      }
    }
  }

  return tiles;
}

/******************************************************************************/
Barebones::TileList AreaOfEffectSkill::GetAffectedTiles(UrsineEngine::GameObject& aBoard,
                                                        const TileLocation& aSourceLocation)
{
  TileList tiles;

  int leftEdge = aSourceLocation.first - mRadius;
  int rightEdge = aSourceLocation.first + mRadius;
  int bottomEdge = aSourceLocation.second - mRadius;
  int topEdge = aSourceLocation.second + mRadius;

  for(int column = leftEdge; column <= rightEdge; ++column)
  {
    for(int row = bottomEdge; row <= topEdge; ++row)
    {
      tiles.emplace_back(TileLocation(column, row));
    }
  }

  return tiles;
}

/******************************************************************************/
Barebones::TileList AreaOfEffectSkill::GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                                           const TileLocation& aSourceLocation)
{
  // Highlight all affected tiles.
  return GetAffectedTiles(aBoard, aSourceLocation);
}
