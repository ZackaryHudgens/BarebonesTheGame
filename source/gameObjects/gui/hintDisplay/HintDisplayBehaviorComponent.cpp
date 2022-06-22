#include "HintDisplayBehaviorComponent.hpp"

#include "HintDisplayTakingTurnState.hpp"

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
    mState = std::make_unique<HintDisplayState>(*parent);
    mState->OnEnter();
  }
}

/******************************************************************************/
void HintDisplayBehaviorComponent::HandlePlayerTurnBegan(PlayerBehaviorComponent& aPlayer)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    if(mState != nullptr)
    {
      mState->OnExit();
    }

    if(dynamic_cast<HumanPlayerBehaviorComponent*>(&aPlayer) != nullptr)
    {
      mState = std::make_unique<HintDisplayTakingTurnState>(*parent);
    }
    else
    {
      mState = std::make_unique<HintDisplayState>(*parent);
    }

    mState->OnEnter();
  }
}
