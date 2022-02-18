#include "HumanPlayerInputComponent.hpp"

using Barebones::HumanPlayerInputComponent;

/******************************************************************************/
HumanPlayerInputComponent::HumanPlayerInputComponent()
  : InputComponent()
  , mState(nullptr)
  , mEnabled(false)
{
}

/******************************************************************************/
void HumanPlayerInputComponent::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                 int aMods)
{
  if(mState != nullptr &&
     mEnabled)
  {
    auto newState = mState->HandleKeyPressed(aCode,
                                             aMods);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}

/******************************************************************************/
void HumanPlayerInputComponent::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                  int aMods)
{
  if(mState != nullptr &&
     mEnabled)
  {
    auto newState = mState->HandleKeyRepeated(aCode,
                                              aMods);
    if(newState != nullptr)
    {
      mState.swap(newState);
    }
  }
}
