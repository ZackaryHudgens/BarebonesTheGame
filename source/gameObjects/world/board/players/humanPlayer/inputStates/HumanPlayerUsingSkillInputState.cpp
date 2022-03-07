#include "HumanPlayerUsingSkillInputState.hpp"

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerDefaultInputState.hpp"

using Barebones::HumanPlayerUsingSkillInputState;

/******************************************************************************/
HumanPlayerUsingSkillInputState::HumanPlayerUsingSkillInputState(UrsineEngine::GameObject& aPlayer,
                                                                 CharacterSkillComponent& aSkill)
  : HumanPlayerInputState(aPlayer)
  , mSkill(&aSkill)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerUsingSkillInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                                    int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  auto board = GetBoard();
  if(board != nullptr)
  {
    auto layoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
    if(layoutComponent != nullptr)
    {
      auto currentLocation = layoutComponent->GetPlayerLocation();

      switch(aCode)
      {
        case UrsineEngine::KeyCode::eKEY_UP:
        case UrsineEngine::KeyCode::eKEY_W:
        {
          layoutComponent->SetPlayerLocation(TileLocation(currentLocation.first,
                                                          currentLocation.second + 1));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_DOWN:
        case UrsineEngine::KeyCode::eKEY_S:
        {
          layoutComponent->SetPlayerLocation(TileLocation(currentLocation.first,
                                                          currentLocation.second - 1));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_LEFT:
        case UrsineEngine::KeyCode::eKEY_A:
        {
          layoutComponent->SetPlayerLocation(TileLocation(currentLocation.first - 1,
                                                          currentLocation.second));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_RIGHT:
        case UrsineEngine::KeyCode::eKEY_D:
        {
          layoutComponent->SetPlayerLocation(TileLocation(currentLocation.first + 1,
                                                          currentLocation.second));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ENTER:
        {
          // If the current position is valid for executing the skill,
          // execute it and revert to a default board input state.
          if(mSkill->IsTileValid(*board,
                                 layoutComponent->GetPlayerLocation()))
          {
            mSkill->Execute(*board,
                            layoutComponent->GetPlayerLocation());

            auto player = GetPlayer();
            if(player != nullptr)
            {
              newState = std::make_unique<HumanPlayerDefaultInputState>(*player);
              newState->SetBoard(*board);
            }
          }
          break;
        }
        default:
        {
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
