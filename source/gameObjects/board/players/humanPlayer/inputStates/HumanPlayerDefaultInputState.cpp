#include "HumanPlayerDefaultInputState.hpp"

#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"

#include "HumanPlayerUsingSkillInputState.hpp"

#include "ActionFactory.hpp"
#include "MenuFactory.hpp"
#include "MenuLayoutComponent.hpp"
#include "SkillActionBehaviorComponent.hpp"

#include "CharacterSkillComponent.hpp"

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
  if(player != nullptr)
  {
    auto board = player->GetParent();
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
            // If there is a character at the player's current location,
            // then create a menu containing all of that character's
            // available skills.
            auto character = layoutComponent->GetCharacterAtLocation(currentLocation);
            if(character != nullptr)
            {
              CreateSkillMenu(*character);
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
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerDefaultInputState::HandleSkillSelected(CharacterSkillComponent& aSkill)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  // When a skill is selected, swap to the Using Skill input state.
  auto player = GetPlayer();
  if(player != nullptr)
  {
    newState = std::make_unique<HumanPlayerUsingSkillInputState>(*player,
                                                                 aSkill);
  }

  return newState;
}

/******************************************************************************/
void HumanPlayerDefaultInputState::CreateSkillMenu(UrsineEngine::GameObject& aObject)
{
  auto skills = aObject.GetComponentsOfType<CharacterSkillComponent>();
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

        auto skillIcon = skill->GetIcon();
        action->AddComponent(std::move(skillIcon));
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
