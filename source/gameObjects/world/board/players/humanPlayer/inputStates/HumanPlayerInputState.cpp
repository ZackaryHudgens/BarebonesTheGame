#include "HumanPlayerInputState.hpp"

#include "HumanPlayerInputComponent.hpp"

using Barebones::HumanPlayerInputState;

/******************************************************************************/
HumanPlayerInputState::HumanPlayerInputState(UrsineEngine::GameObject& aPlayer)
  : mPlayer(&aPlayer)
  , mBoard(nullptr)
{
}
