#include "BoardInitialState.hpp"

#include "BoardDefaultState.hpp"

using Barebones::BoardInitialState;

/******************************************************************************/
BoardInitialState::BoardInitialState(UrsineEngine::GameObject& aBoard)
  : BoardState(aBoard)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardState> BoardInitialState::HandleCameraFinishedMovingToBoard()
{
  // Returns to the default state.
  std::unique_ptr<BoardState> newState = nullptr;

  auto board = GetBoard();
  if(board != nullptr)
  {
    newState = std::make_unique<BoardDefaultState>(*board);
  }

  return std::move(newState);
}
