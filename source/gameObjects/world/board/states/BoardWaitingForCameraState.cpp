#include "BoardWaitingForCameraState.hpp"

#include "Signals.hpp"

using Barebones::BoardWaitingForCameraState;

/******************************************************************************/
BoardWaitingForCameraState::BoardWaitingForCameraState(UrsineEngine::GameObject& aBoard)
  : BoardState(aBoard)
  , mWaiting(true)
{
  CameraFinishedMovingToBoard.Connect(mObserver, [this](UrsineEngine::GameObject& aBoard)
  {
    this->HandleCameraFinishedMovingToBoard(aBoard);
  });
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardState> BoardWaitingForCameraState::Update(double aTime)
{
  std::unique_ptr<BoardState> newState = nullptr;

  if(!mWaiting)
  {
    auto board = GetBoard();
    if(board != nullptr)
    {
      newState = std::make_unique<BoardState>(*board);
      BoardFinishedInitialSequence.Notify(*board);
    }
  }

  return std::move(newState);
}

/******************************************************************************/
void BoardWaitingForCameraState::HandleCameraFinishedMovingToBoard(UrsineEngine::GameObject& aBoard)
{
  auto board = GetBoard();
  if(board != nullptr)
  {
    if(&aBoard == board)
    {
      mWaiting = false;
    }
  }
}
