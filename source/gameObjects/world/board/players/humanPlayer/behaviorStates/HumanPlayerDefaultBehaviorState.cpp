#include "HumanPlayerDefaultBehaviorState.hpp"

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

  return newState;
}
