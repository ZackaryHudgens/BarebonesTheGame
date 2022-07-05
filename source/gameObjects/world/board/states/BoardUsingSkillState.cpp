#include "BoardUsingSkillState.hpp"

#include "BoardDefaultState.hpp"

#include "BoardLayoutComponent.hpp"
#include "TileBehaviorComponent.hpp"

#include "Colors.hpp"
#include "Signals.hpp"

using Barebones::BoardUsingSkillState;

/******************************************************************************/
BoardUsingSkillState::BoardUsingSkillState(UrsineEngine::GameObject& aBoard,
                                           Skill& aSkill)
  : BoardState(aBoard)
  , mSkill(&aSkill)
  , mFocusedTile(nullptr)
  , mHighlightIntensity(0.7)
{
  BoardFocusedTileChanged.Connect(mObserver, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleBoardFocusedTileChanged(aBoard);
  });
}

/******************************************************************************/
void BoardUsingSkillState::OnEnter()
{
  HighlightTiles();
}

/******************************************************************************/
void BoardUsingSkillState::OnExit()
{
  RemoveHighlights();
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardState> BoardUsingSkillState::HandleSkillExecuted(Skill& aSkill)
{
  std::unique_ptr<BoardState> newState = nullptr;

  // Revert to the default state.
  auto board = GetBoard();
  if(board != nullptr)
  {
    newState = std::make_unique<BoardDefaultState>(*board);
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardState> BoardUsingSkillState::HandleSkillCancelled(Skill& aSkill)
{
  return HandleSkillExecuted(aSkill);
}

/******************************************************************************/
void BoardUsingSkillState::HandleBoardFocusedTileChanged(UrsineEngine::GameObject& aBoard)
{
  RemoveHighlights();
  HighlightTiles();
}

/******************************************************************************/
void BoardUsingSkillState::RemoveHighlights()
{
  // First, un-highlight all highlighted tiles.
  for(auto& highlightedTile : mHighlightedTiles)
  {
    auto tileBehaviorComponent = highlightedTile->GetFirstComponentOfType<TileBehaviorComponent>();
    if(tileBehaviorComponent != nullptr)
    {
      tileBehaviorComponent->SetHighlightIntensity(0.0);
    }
  }
  mHighlightedTiles.clear();

  // Also un-highlight the focused tile.
  if(mFocusedTile != nullptr)
  {
    auto tileBehaviorComponent = mFocusedTile->GetFirstComponentOfType<TileBehaviorComponent>();
    if(tileBehaviorComponent != nullptr)
    {
      tileBehaviorComponent->SetHighlightIntensity(0.0);
    }
  }
  mFocusedTile = nullptr;
}

/******************************************************************************/
void BoardUsingSkillState::HighlightTiles()
{
  // Retrieve all tiles to highlight from the selected skill and highlight them.
  auto board = GetBoard();
  if(board != nullptr)
  {
    auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      auto focusedLocation = boardLayoutComponent->GetFocusedTileLocation();

      if(mSkill != nullptr)
      {
        auto tilesToHighlight = mSkill->GetTilesToHighlight(*board, focusedLocation);
        for(const auto& tileLocation : tilesToHighlight)
        {
          auto tile = boardLayoutComponent->GetTileAtLocation(tileLocation);
          if(tile != nullptr)
          {
            auto tileBehaviorComponent = tile->GetFirstComponentOfType<TileBehaviorComponent>();
            if(tileBehaviorComponent != nullptr)
            {
              tileBehaviorComponent->SetHighlightColor(glm::vec4(LIGHT_COLOR, 1.0));
              tileBehaviorComponent->SetHighlightIntensity(mHighlightIntensity);

              mHighlightedTiles.emplace_back(tile);
            }
          }
        }
      }

      // Also highlight the currently focused tile.
      auto focusedTile = boardLayoutComponent->GetTileAtLocation(focusedLocation);
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
