#include "BoardDefaultState.hpp"

#include "BoardUsingSkillState.hpp"

#include "BoardLayoutComponent.hpp"
#include "TileBehaviorComponent.hpp"

#include "Colors.hpp"
#include "Signals.hpp"

using Barebones::BoardDefaultState;

/******************************************************************************/
BoardDefaultState::BoardDefaultState(UrsineEngine::GameObject& aBoard)
  : BoardState(aBoard)
  , mFocusedTile(nullptr)
  , mHighlightIntensity(0.7)
{
  BoardFocusedTileChanged.Connect(mObserver, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleBoardFocusedTileChanged(aBoard);
  });
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
          tileBehaviorComponent->SetHighlightColor(glm::vec4(BACKGROUND_COLOR, 1.0));
          tileBehaviorComponent->SetHighlightIntensity(mHighlightIntensity);
          mFocusedTile = focusedTile;
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
std::unique_ptr<Barebones::BoardState> BoardDefaultState::HandleSkillSelected(Skill& aSkill)
{
  std::unique_ptr<BoardState> newState = nullptr;

  // Swap to the Using Skill state.
  auto board = GetBoard();
  if(board != nullptr)
  {
    newState = std::make_unique<BoardUsingSkillState>(*board, aSkill);
  }

  return newState;
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
          tileBehaviorComponent->SetHighlightColor(glm::vec4(BACKGROUND_COLOR, 1.0));
          tileBehaviorComponent->SetHighlightIntensity(mHighlightIntensity);
          mFocusedTile = focusedTile;
        }
      }
    }
  }
}
