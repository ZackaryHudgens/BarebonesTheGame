#include "ScreenTransitionDefaultState.hpp"

#include "ScreenTransitionFadingOutState.hpp"

using Barebones::ScreenTransitionDefaultState;

/******************************************************************************/
ScreenTransitionDefaultState::ScreenTransitionDefaultState(UrsineEngine::GameObject& aParent)
  : ScreenTransitionState(aParent)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::ScreenTransitionState> ScreenTransitionDefaultState::HandleScreenTransitionRequested(const SceneType& aType)
{
  std::unique_ptr<ScreenTransitionState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    newState = std::make_unique<ScreenTransitionFadingOutState>(*parent, aType);
  }

  return newState;
}
