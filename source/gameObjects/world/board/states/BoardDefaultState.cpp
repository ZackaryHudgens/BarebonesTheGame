#include "BoardDefaultState.hpp"

#include "BoardLayoutComponent.hpp"

#include "TileBehaviorComponent.hpp"

#include "Colors.hpp"

using Barebones::BoardDefaultState;

/******************************************************************************/
BoardDefaultState::BoardDefaultState(UrsineEngine::GameObject& aBoard)
  : BoardState(aBoard)
  , mHighlightIntensity(0.7)
{
}

/******************************************************************************/
void BoardDefaultState::OnEnter()
{
  // Upon entering this state, set the highlight color and intensity of the
  // currently focused tile.
  auto board = GetBoard();
  if(board != nullptr)
  {
    auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      auto location = boardLayoutComponent->GetFocusedTileLocation();
      auto focusedTile = boardLayoutComponent->GetTileAtLocation(location);
      if(focusedTile != nullptr)
      {
        auto tileBehaviorComponent = focusedTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(tileBehaviorComponent != nullptr)
        {
          tileBehaviorComponent->SetHighlightColor(glm::vec4(DARK_COLOR, 1.0));
          tileBehaviorComponent->SetHighlightIntensity(mHighlightIntensity);
        }
      }
    }
  }
}

/******************************************************************************/
void BoardDefaultState::OnExit()
{
  // Upon exiting this state, un-highlight the focused tile.
  if(mFocusedTile != nullptr)
  {
    auto tileBehaviorComponent = mFocusedTile->GetFirstComponentOfType<TileBehaviorComponent>();
    if(tileBehaviorComponent != nullptr)
    {
      tileBehaviorComponent->SetHighlightIntensity(0.0);
    }
  }
}

/******************************************************************************/
void BoardDefaultState::HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard)
{
  if(GetBoard() == &aBoard)
  {
    auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      auto location = boardLayoutComponent->GetFocusedTileLocation();
      auto focusedTile = boardLayoutComponent->GetTileAtLocation(location);
      if(focusedTile != nullptr)
      {
        // Un-highlight the currently focused tile.
        if(mFocusedTile != nullptr)
        {
          auto tileBehaviorComponent = mFocusedTile->GetFirstComponentOfType<TileBehaviorComponent>();
          if(tileBehaviorComponent != nullptr)
          {
            tileBehaviorComponent->SetHighlightIntensity(0.0);
          }
        }

        // Highlight the newly focused tile.
        auto tileBehaviorComponent = focusedTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(tileBehaviorComponent != nullptr)
        {
          tileBehaviorComponent->SetHighlightIntensity(mHighlightIntensity);
          mFocusedTile = focusedTile;
        }
      }
    }
  }
}
