#include "HintDisplayDefaultState.hpp"

#include "HintDisplayTakingTurnState.hpp"

#include "HumanPlayerBehaviorComponent.hpp"

using Barebones::HintDisplayDefaultState;

/******************************************************************************/
HintDisplayDefaultState::HintDisplayDefaultState(UrsineEngine::GameObject& aParent)
  : HintDisplayState(aParent)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::HintDisplayState> HintDisplayDefaultState::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  std::unique_ptr<HintDisplayState> newState = nullptr;

  if(dynamic_cast<HumanPlayerBehaviorComponent*>(&aPlayer) != nullptr)
  {
    auto parent = GetParent();
    if(parent != nullptr)
    {
      newState = std::make_unique<HintDisplayTakingTurnState>(*parent);
    }
  }

  return newState;
}
