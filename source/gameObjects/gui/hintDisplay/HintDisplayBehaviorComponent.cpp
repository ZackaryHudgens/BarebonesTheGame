#include "HintDisplayBehaviorComponent.hpp"

#include "HintDisplayDefaultState.hpp"

#include "HumanPlayerBehaviorComponent.hpp"

#include "Signals.hpp"

using Barebones::HintDisplayBehaviorComponent;

/******************************************************************************/
HintDisplayBehaviorComponent::HintDisplayBehaviorComponent()
  : Component()
  , mState(nullptr)
{
  PlayerTurnBegan.Connect(*this, [this](PlayerBehaviorComponent& aPlayer)
  {
    this->HandlePlayerTurnBegan(aPlayer);
  });
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
  if(mState != nullptr)
  {
    auto newState = mState->HandlePlayerTurnBegan(aPlayer);
    if(newState != nullptr)
    {
      mState->OnExit();
      mState.swap(newState);
      mState->OnEnter();
    }
  }
}
