#include "HumanPlayerInputComponent.hpp"

#include "HumanPlayerDefaultInputState.hpp"

using Barebones::HumanPlayerInputComponent;

/******************************************************************************/
HumanPlayerInputComponent::HumanPlayerInputComponent()
  : InputComponent()
  , mState(nullptr)
  , mEnabled(false)
{
  UrsineEngine::KeyPressed.Connect(*this, [this](const UrsineEngine::KeyCode& aCode,
                                                 int aMods)
  {
    this->HandleKeyPressed(aCode,
                           aMods);
  });

  UrsineEngine::KeyRepeated.Connect(*this, [this](const UrsineEngine::KeyCode& aCode,
                                                  int aMods)
  {
    this->HandleKeyRepeated(aCode,
                            aMods);
  });
}

/******************************************************************************/
void HumanPlayerInputComponent::SetBoard(UrsineEngine::GameObject& aBoard)
{
  mState = std::make_unique<HumanPlayerDefaultInputState>(aBoard);
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
