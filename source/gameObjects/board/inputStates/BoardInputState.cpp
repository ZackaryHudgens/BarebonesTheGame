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
  std::unique_ptr<BoardInputState> newState = nullptr;
  newState = ProtectedHandleKeyPressed(aCode,
                                       aMods);
  return newState;
}

/******************************************************************************/
std::unique_ptr<BoardInputState> BoardInputState::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                    int aMods)
{
  std::unique_ptr<BoardInputState> newState = nullptr;
  newState = ProtectedHandleKeyRepeated(aCode,
                                        aMods);
  return newState;
}

/******************************************************************************/
std::unique_ptr<BoardInputState> BoardInputState::ProtectedHandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                            int aMods)
{
  return nullptr;
}

/******************************************************************************/
std::unique_ptr<BoardInputState> BoardInputState::ProtectedHandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                             int aMods)
{
  return nullptr;
}
