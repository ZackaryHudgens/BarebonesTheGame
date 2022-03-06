#include "HumanPlayerInputState.hpp"

using Barebones::HumanPlayerInputState;

/******************************************************************************/
HumanPlayerInputState::HumanPlayerInputState(UrsineEngine::GameObject& aPlayer)
  : mPlayer(&aPlayer)
  , mBoard(nullptr)
{
}
