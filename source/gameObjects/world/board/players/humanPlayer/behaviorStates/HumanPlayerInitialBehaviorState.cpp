#include "HumanPlayerInitialBehaviorState.hpp"

using Barebones::HumanPlayerInitialBehaviorState;

/******************************************************************************/
HumanPlayerInitialBehaviorState::HumanPlayerInitialBehaviorState(UrsineEngine::GameObject& aPlayer)
  : HumanPlayerBehaviorState(aPlayer)
{
}

/******************************************************************************/
void HumanPlayerInitialBehaviorState::OnEnter()
{
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerBehaviorState> HumanPlayerInitialBehaviorState::HandleCharacterFinishedSpawning(CharacterBehaviorComponent& aCharacter)
{
  std::unique_ptr<HumanPlayerBehaviorState> newState = nullptr;

  return newState;
}
