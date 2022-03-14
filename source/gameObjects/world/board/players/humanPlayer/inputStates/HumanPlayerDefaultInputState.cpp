#include "HumanPlayerDefaultInputState.hpp"

#include <Environment.hpp>

#include "PlayerBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "ActionFactory.hpp"
#include "MenuFactory.hpp"
#include "MenuLayoutComponent.hpp"
#include "SkillActionBehaviorComponent.hpp"

#include "CharacterBehaviorComponent.hpp"
#include "Skill.hpp"

#include <iostream>

using Barebones::HumanPlayerDefaultInputState;

/******************************************************************************/
HumanPlayerDefaultInputState::HumanPlayerDefaultInputState(UrsineEngine::GameObject& aPlayer)
  : HumanPlayerInputState(aPlayer)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerDefaultInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                                 int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  auto player = GetPlayer();
  auto board = GetBoard();
  if(player != nullptr &&
     board != nullptr)
  {
    auto playerBehaviorComponent = player->GetFirstComponentOfType<PlayerBehaviorComponent>();
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
        case UrsineEngine::KeyCode::eKEY_ENTER:
        {
          // If there is a character at the player's current location,
          // then create a menu containing all of that character's
          // available skills.
          auto character = boardLayoutComponent->GetCharacterAtLocation(currentLocation);
          if(character != nullptr)
          {
            CreateSkillMenu(*character);
          }

          break;
        }
        case UrsineEngine::KeyCode::eKEY_ESCAPE:
        {
          // End the player's turn.
          auto player = GetPlayer();
          if(player != nullptr)
          {
            auto behaviorComponent = player->GetFirstComponentOfType<PlayerBehaviorComponent>();
            if(behaviorComponent != nullptr)
            {
              behaviorComponent->EndTurn();
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
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerDefaultInputState::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
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

/******************************************************************************/
void HumanPlayerDefaultInputState::CreateSkillMenu(UrsineEngine::GameObject& aObject)
{
  auto characterBehaviorComponent = aObject.GetFirstComponentOfType<CharacterBehaviorComponent>();
  if(characterBehaviorComponent != nullptr)
  {
    auto skills = characterBehaviorComponent->GetSkills();
    if(!skills.empty())
    {
      // Create a new menu object.
      auto menu = MenuFactory::CreateMenu(MenuType::eSKILL,
                                          "skillMenu");
      auto menuLayout = menu->GetFirstComponentOfType<MenuLayoutComponent>();
      if(menuLayout != nullptr)
      {
        // Add each of this character's skills to the menu.
        for(auto& skill : skills)
        {
          auto action = ActionFactory::CreateAction(ActionType::eSKILL,
                                                    skill->GetName());
          auto skillAction = action->GetFirstComponentOfType<SkillActionBehaviorComponent>();
          skillAction->SetSkill(*skill);
          menuLayout->AddAction(std::move(action));
        }
      }

      // Add the new menu to the foreground of the current scene.
      auto scene = env.GetCurrentScene();
      if(scene != nullptr)
      {
        auto foreground = scene->GetForeground();
        if(foreground != nullptr)
        {
          foreground->AddChild(std::move(menu));
        }
      }
    }
  }
}
