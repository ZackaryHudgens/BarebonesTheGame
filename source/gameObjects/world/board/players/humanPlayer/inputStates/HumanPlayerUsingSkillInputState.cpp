#include "HumanPlayerUsingSkillInputState.hpp"

#include <algorithm>

#include "Signals.hpp"

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerBehaviorComponent.hpp"
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
      auto currentLocation = playerBehaviorComponent->GetLocation();
      switch(aCode)
      {
        // For player movement, first check if a tile exists at the new location
        // on the board. If it does, update the player's location.
        case UrsineEngine::KeyCode::eKEY_UP:
        case UrsineEngine::KeyCode::eKEY_W:
        {
          TileLocation newLocation = currentLocation;
          newLocation.second += 1;

          auto tile = boardLayoutComponent->GetTileAtLocation(newLocation);
          if(tile != nullptr)
          {
            playerBehaviorComponent->SetLocation(newLocation);
          }

          break;
        }
        case UrsineEngine::KeyCode::eKEY_DOWN:
        case UrsineEngine::KeyCode::eKEY_S:
        {
          TileLocation newLocation = currentLocation;
          newLocation.second -= 1;

          auto tile = boardLayoutComponent->GetTileAtLocation(newLocation);
          if(tile != nullptr)
          {
            playerBehaviorComponent->SetLocation(newLocation);
          }

          break;
        }
        case UrsineEngine::KeyCode::eKEY_LEFT:
        case UrsineEngine::KeyCode::eKEY_A:
        {
          TileLocation newLocation = currentLocation;
          newLocation.first -= 1;

          auto tile = boardLayoutComponent->GetTileAtLocation(newLocation);
          if(tile != nullptr)
          {
            playerBehaviorComponent->SetLocation(newLocation);
          }

          break;
        }
        case UrsineEngine::KeyCode::eKEY_RIGHT:
        case UrsineEngine::KeyCode::eKEY_D:
        {
          TileLocation newLocation = currentLocation;
          newLocation.first += 1;

          auto tile = boardLayoutComponent->GetTileAtLocation(newLocation);
          if(tile != nullptr)
          {
            playerBehaviorComponent->SetLocation(newLocation);
          }

          break;
        }
        case UrsineEngine::KeyCode::eKEY_Z:
        {
          CameraZoomChangeRequested.Notify(2.5);
          break;
        }
        case UrsineEngine::KeyCode::eKEY_X:
        {
          CameraZoomChangeRequested.Notify(0.0);
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ENTER:
        {
          // If the player's location is valid for using the current skill,
          // execute it, then return to the default input state.
          if(mSkill != nullptr)
          {
            if(mSkill->IsTileValid(*board,
                                   currentLocation))
            {
              mSkill->Execute(*board,
                              currentLocation);
              newState = std::make_unique<HumanPlayerDefaultInputState>(*player);
              newState->SetBoard(*board);
            }
          }
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ESCAPE:
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
