#include "HumanPlayerUsingSkillInputState.hpp"

#include <algorithm>

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerDefaultInputState.hpp"

using Barebones::HumanPlayerUsingSkillInputState;

/******************************************************************************/
HumanPlayerUsingSkillInputState::HumanPlayerUsingSkillInputState(UrsineEngine::GameObject& aPlayer,
                                                                 Skill& aSkill)
  : HumanPlayerInputState(aPlayer)
  , mSkill(&aSkill)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerUsingSkillInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                                    int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerUsingSkillInputState::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                                                     int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  switch(aCode)
  {
    case UrsineEngine::KeyCode::eKEY_ESCAPE:
    case UrsineEngine::KeyCode::eKEY_ENTER:
    {
      break;
    }
    default:
    {
      newState = HandleKeyPressed(aCode,
                                  aMods);
      break;
    }
  }
  return newState;
}
