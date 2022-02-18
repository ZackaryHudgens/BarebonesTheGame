#include "HumanPlayerDefaultInputState.hpp"

#include <Environment.hpp>

#include "BoardLayoutComponent.hpp"

#include "ActionFactory.hpp"
#include "MenuFactory.hpp"
#include "MenuLayoutComponent.hpp"
#include "SkillActionBehaviorComponent.hpp"

#include "CharacterSkillComponent.hpp"

using Barebones::HumanPlayerDefaultInputState;

/******************************************************************************/
HumanPlayerDefaultInputState::HumanPlayerDefaultInputState(UrsineEngine::GameObject& aBoard)
  : HumanPlayerInputState(aBoard)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::HumanPlayerInputState> HumanPlayerDefaultInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                                 int aMods)
{
  std::unique_ptr<HumanPlayerInputState> newState = nullptr;

  auto layoutComponent = GetBoard()->GetFirstComponentOfType<BoardLayoutComponent>();
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

    // Add the new menu to the current scene.
    auto scene = env.GetCurrentScene();
    if(scene != nullptr)
    {
      scene->AddObject(std::move(menu));
    }
  }
}
