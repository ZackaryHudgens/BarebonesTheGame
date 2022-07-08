#include "HumanPlayerDefaultBehaviorState.hpp"

#include "HumanPlayerBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerEditingBehaviorState.hpp"

using Barebones::HumanPlayerDefaultBehaviorState;

/******************************************************************************/
HumanPlayerDefaultBehaviorState::HumanPlayerDefaultBehaviorState(UrsineEngine::GameObject& aPlayer)
  : HumanPlayerBehaviorState(aPlayer)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerBehaviorState> HumanPlayerDefaultBehaviorState::HandleCharacterSelectedFromRewardsMenu(const CharacterType& aType)
{
  std::unique_ptr<HumanPlayerBehaviorState> newState = nullptr;

  // Swap to the editing state.
  auto player = GetPlayer();
  if(player != nullptr)
  {
    newState = std::make_unique<HumanPlayerEditingBehaviorState>(*player, aType);
  }

  return newState;
}
