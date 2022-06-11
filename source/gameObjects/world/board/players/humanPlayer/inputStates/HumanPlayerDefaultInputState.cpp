#include "HumanPlayerDefaultInputState.hpp"

#include <Environment.hpp>

#include "HumanPlayerBehaviorComponent.hpp"

#include "BoardLayoutComponent.hpp"

#include "MenuFactory.hpp"
#include "MenuLayoutComponent.hpp"

#include "CharacterBehaviorComponent.hpp"
#include "Skill.hpp"

#include "Signals.hpp"

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
        case UrsineEngine::KeyCode::eKEY_Q:
        {
          // Create a pause menu and add it to the scene.
          auto pauseMenu = MenuFactory::CreateMenu(MenuType::ePAUSE, "pauseMenu");
          auto scene = env.GetCurrentScene();
          if(scene != nullptr)
          {
            scene->AddObject(std::move(pauseMenu));
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
            auto characterBehaviorComponent = character->GetFirstComponentOfType<CharacterBehaviorComponent>();
            if(characterBehaviorComponent != nullptr)
            {
              // Only create a menu if the character is on the player's side.
              if(characterBehaviorComponent->GetSide() == playerBehaviorComponent->GetSide())
              {
                auto skillMenu = MenuFactory::CreateMenu(MenuType::eSKILL, "skillMenu");
                auto skills = characterBehaviorComponent->GetSkills();
                PopulateSkillMenu(*skillMenu.get(), skills);

                // Add the menu to the foreground of the current scene.
                auto scene = env.GetCurrentScene();
                if(scene != nullptr)
                {
                  auto foreground = scene->GetForeground();
                  if(foreground != nullptr)
                  {
                    foreground->AddChild(std::move(skillMenu));
                  }
                }
              }
            }
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
void HumanPlayerDefaultInputState::PopulateSkillMenu(UrsineEngine::GameObject& aMenu,
                                                     const std::vector<Skill*>& aSkills)
{
  auto boardObject = GetBoard();
  auto playerObject = GetPlayer();
  auto menuLayoutComponent = aMenu.GetFirstComponentOfType<MenuLayoutComponent>();
  if(boardObject != nullptr &&
     playerObject != nullptr &&
     menuLayoutComponent != nullptr)
  {
    auto humanPlayerBehaviorComponent = playerObject->GetFirstComponentOfType<HumanPlayerBehaviorComponent>();
    if(humanPlayerBehaviorComponent != nullptr)
    {
      auto currentLocation = humanPlayerBehaviorComponent->GetLocation();

      // For each skill, create an action that selects it on execution.
      for(const auto& skill : aSkills)
      {
        auto skillAction = std::make_unique<MenuAction>(skill->GetName(),
                                                        skill->GetDescription());
        auto selectSkill = [skill, boardObject]() { skill->Select(*boardObject); };
        skillAction->SetFunction(selectSkill);

        // If the skill is disabled, disable the action before adding it to the menu.
        if(!skill->IsEnabled())
        {
          skillAction->SetEnabled(false);
        }

        menuLayoutComponent->AddAction(std::move(skillAction));
      }
    }
  }
}

