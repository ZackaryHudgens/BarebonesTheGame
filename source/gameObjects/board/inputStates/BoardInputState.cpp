#include "BoardInputState.hpp"

using Barebones::BoardInputState;

/******************************************************************************/
BoardInputState::BoardInputState(UrsineEngine::GameObject& aObject,
                                 int aXPos,
                                 int aYPos)
  : mParent(&aObject)
  , mPlayerXLocation(aXPos)
  , mPlayerYLocation(aYPos)
{
}

/******************************************************************************/
std::unique_ptr<BoardInputState> BoardInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                   int aMods)
{
  return nullptr;
}
