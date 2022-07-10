#include "HumanPlayerVictoryInputState.hpp"

using Barebones::HumanPlayerVictoryInputState;

/******************************************************************************/
HumanPlayerVictoryInputState::HumanPlayerVictoryInputState(UrsineEngine::GameObject& aPlayer)
  : HumanPlayerMovableInputState(aPlayer)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerVictoryInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                                    int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  switch(aCode)
  {
    case UrsineEngine::KeyCode::eKEY_Q:
    {
      break;
    }
    default:
    {
      newState = HumanPlayerMovableInputState::HandleKeyPressed(aCode, aMods);
      break;
    }
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerVictoryInputState::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                                                     int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  switch(aCode)
  {
    case UrsineEngine::KeyCode::eKEY_Q:
    {
      break;
    }
    default:
    {
      newState = HumanPlayerMovableInputState::HandleKeyRepeated(aCode, aMods);
      break;
    }
  }
  return newState;
}
