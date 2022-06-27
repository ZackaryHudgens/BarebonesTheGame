#include "MoveSkillEffectBehaviorComponent.hpp"

#include <algorithm>

#include "MoveSkill.hpp"

#include "BoardLayoutComponent.hpp"
#include "TileBehaviorComponent.hpp"

#include "Colors.hpp"
#include "Signals.hpp"

using Barebones::MoveSkillEffectBehaviorComponent;

/******************************************************************************/
MoveSkillEffectBehaviorComponent::MoveSkillEffectBehaviorComponent(Barebones::MoveSkill& aSkill)
  : Component()
  , mBoard(nullptr)
  , mMoveSkill(&aSkill)
  , mStartingLocation(-1, -1)
{
  BoardFocusedTileChanged.Connect(*this, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleBoardFocusedTileChanged(aBoard);
  });
}

/******************************************************************************/
void MoveSkillEffectBehaviorComponent::HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard)
{
  // Find the path in the shortest path list that ends in the player's
  // current location, then highlight each tile in that path.
  if(mBoard != nullptr &&
     mMoveSkill != nullptr)
  {
    auto boardLayoutComponent = mBoard->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      auto tileLocation = boardLayoutComponent->GetFocusedTileLocation();

      // Returns true if playerLocation is the last TileLocation in the TileList.
      auto isPath = [&tileLocation](const TilePath& aPath)
      {
        bool success = false;

        if(!aPath.first.empty())
        {
          success = (aPath.first.back() == tileLocation);
        }

        return success;
      };

      // Un-highlight each currently highlighted tile.
      for(const auto& highlightedLocation : mHighlightedTiles)
      {
        auto tile = boardLayoutComponent->GetTileAtLocation(highlightedLocation);
        if(tile != nullptr)
        {
          auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
          if(tileBehaviorComponent != nullptr)
          {
            tileBehaviorComponent->SetHighlightColor(LIGHT_COLOR);
            tileBehaviorComponent->SetHighlightIntensity(0.7);
          }
        }
      }
      mHighlightedTiles.clear();

      // If the tile is a valid movement, highlight each tile
      // along the path taken to get there.
      if(mMoveSkill->IsTileValid(*mBoard, mStartingLocation, tileLocation))
      {
        auto path = std::find_if(mShortestPaths.begin(),
                                 mShortestPaths.end(),
                                 isPath);
        if(path != mShortestPaths.end())
        {
          // Highlight each tile in the path.
          for(const auto& location : path->first)
          {
            auto tile = boardLayoutComponent->GetTileAtLocation(location);
            if(tile != nullptr)
            {
              auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
              if(tileBehaviorComponent != nullptr)
              {
                tileBehaviorComponent->SetHighlightColor(BACKGROUND_COLOR);
                tileBehaviorComponent->SetHighlightIntensity(0.7);

                mHighlightedTiles.emplace_back(location);
              }
            }
          }
        }
      }
    }
  }
}
