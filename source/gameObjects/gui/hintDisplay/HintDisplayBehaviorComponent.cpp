#include "HintDisplayBehaviorComponent.hpp"

#include "HintDisplayDefaultState.hpp"

using Barebones::HintDisplayBehaviorComponent;

/******************************************************************************/
HintDisplayBehaviorComponent::HintDisplayBehaviorComponent()
  : Component()
  , mState(nullptr)
{
}

/******************************************************************************/
void HintDisplayBehaviorComponent::Initialize()
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    mState = std::make_unique<HintDisplayDefaultState>(*parent);
    mState->OnEnter();
  }
}

/******************************************************************************/
void HintDisplayBehaviorComponent::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
}

/******************************************************************************/
void HintDisplayBehaviorComponent::HandlePlayerTurnEnded(PlayerBehaviorComponent& aPlayer)
{
}
