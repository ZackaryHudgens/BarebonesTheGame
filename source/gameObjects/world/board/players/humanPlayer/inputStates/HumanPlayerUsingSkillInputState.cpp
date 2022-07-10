#include "HumanPlayerUsingSkillInputState.hpp"

#include <algorithm>

#include <Environment.hpp>

#include "MenuFactory.hpp"

#include "Signals.hpp"

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerBehaviorComponent.hpp"
#include "HumanPlayerDefaultInputState.hpp"

using Barebones::HumanPlayerUsingSkillInputState;

/******************************************************************************/
HumanPlayerUsingSkillInputState::HumanPlayerUsingSkillInputState(UrsineEngine::GameObject& aPlayer,
                                                                 Skill& aSkill)
  : HumanPlayerMovableInputState(aPlayer)
  , mSkill(&aSkill)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerUsingSkillInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                                    int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  auto player = GetPlayer();
  auto board = GetBoard();
  if(player != nullptr &&
     board != nullptr)
  {
    auto playerBehaviorComponent = player->GetFirstComponentOfType<HumanPlayerBehaviorComponent>();
    auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
    if(playerBehaviorComponent != nullptr &&
       boardLayoutComponent != nullptr)
    {
      auto currentLocation = boardLayoutComponent->GetFocusedTileLocation();
      switch(aCode)
      {
        case UrsineEngine::KeyCode::eKEY_ENTER:
        {
          // If the player's location is valid for using the current skill,
          // execute it, then return to the default input state.
          if(mSkill != nullptr)
          {
            if(mSkill->IsTileValid(*board, currentLocation))
            {
              mSkill->Execute(*board, currentLocation);
              newState = std::make_unique<HumanPlayerDefaultInputState>(*player);
              newState->SetBoard(*board);
            }
          }

          break;
        }
        case UrsineEngine::KeyCode::eKEY_Q:
        {
          // Stop using this skill and return to the default input state.
          newState = std::make_unique<HumanPlayerDefaultInputState>(*player);
          newState->SetBoard(*board);
          
          if(mSkill != nullptr)
          {
            mSkill->Cancel();
          }

          break;
        }
        default:
        {
          newState = HumanPlayerMovableInputState::HandleKeyPressed(aCode, aMods);
          break;
        }
      }

    }
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerUsingSkillInputState::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                                                     int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  switch(aCode)
  {
    case UrsineEngine::KeyCode::eKEY_ENTER:
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
