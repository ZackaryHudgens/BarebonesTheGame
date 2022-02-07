#include "DefaultBoardInputState.hpp"

#include <sstream>

#include <Environment.hpp>

#include "ActionFactory.hpp"
#include "BoardLayoutComponent.hpp"
#include "CharacterSkillComponent.hpp"
#include "MenuFactory.hpp"
#include "MenuLayoutComponent.hpp"
#include "TileBehaviorComponent.hpp"

using Barebones::DefaultBoardInputState;

/******************************************************************************/
DefaultBoardInputState::DefaultBoardInputState(UrsineEngine::GameObject& aObject,
                                               int aXPos,
                                               int aYPos)
  : BoardInputState(aObject, aXPos, aYPos)
{
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> DefaultBoardInputState::ProtectedHandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                              int aMods)
{
  std::unique_ptr<Barebones::BoardInputState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    int x = GetPlayerXLocation();
    int y = GetPlayerYLocation();

    switch(aCode)
    {
      case UrsineEngine::KeyCode::eKEY_UP:
      case UrsineEngine::KeyCode::eKEY_W:
      {
        HoverOverTile(x,
                      y + 1);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_DOWN:
      case UrsineEngine::KeyCode::eKEY_S:
      {
        HoverOverTile(x,
                      y - 1);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_LEFT:
      case UrsineEngine::KeyCode::eKEY_A:
      {
        HoverOverTile(x - 1,
                      y);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_RIGHT:
      case UrsineEngine::KeyCode::eKEY_D:
      {
        HoverOverTile(x + 1,
                      y);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_ENTER:
      {
        // If there is a character at the player's current position,
        // then create a menu containing all of that character's
        // available skills and 
        auto parent = GetParent();
        if(parent != nullptr)
        {
          auto layout = parent->GetFirstComponentOfType<BoardLayoutComponent>();
          if(layout != nullptr)
          {
            auto character = layout->GetCharacterAtPosition(x,
                                                            y);
            if(character != nullptr)
            {
              auto skills = character->GetComponentsOfType<CharacterSkillComponent>();
              if(!skills.empty())
              {
                // Create a new menu object.
                auto menu = MenuFactory::CreateMenu(MenuType::eSKILL,
                                                    "skillMenu");
                auto menuLayout = menu->GetFirstComponentOfType<MenuLayoutComponent>();
                if(menuLayout != nullptr)
                {
                  std::stringstream skillName;
                  int skillIindex = 0;

                  // Add each of this character's skills to the menu.
                  for(auto& skill : skills)
                  {
                    skillName << skill->GetName() << "_" << skillIindex;

                    auto action = ActionFactory::CreateAction(ActionType::eSKILL,
                                                              skillName.str());
                    auto skillIcon = skill->GetIcon();
                    action->AddComponent(std::move(skillIcon));
                    menuLayout->AddAction(std::move(action));

                    skillName.str("");
                    ++skillIindex;
                  }
                }

                // Add the new menu to the current scene.
                auto scene = env.GetCurrentScene();
                if(scene != nullptr)
                {
                  scene->AddObject(std::move(menu));
                }

                // Finally, disable this input state until the user
                // exits the menu.
                SetDisabled(true);
              }
            }
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

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> DefaultBoardInputState::ProtectedHandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                                               int aMods)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    int x = GetPlayerXLocation();
    int y = GetPlayerYLocation();

    switch(aCode)
    {
      case UrsineEngine::KeyCode::eKEY_UP:
      case UrsineEngine::KeyCode::eKEY_W:
      {
        HoverOverTile(x,
                      y + 1);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_DOWN:
      case UrsineEngine::KeyCode::eKEY_S:
      {
        HoverOverTile(x,
                      y - 1);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_LEFT:
      case UrsineEngine::KeyCode::eKEY_A:
      {
        HoverOverTile(x - 1,
                      y);
        break;
      }
      case UrsineEngine::KeyCode::eKEY_RIGHT:
      case UrsineEngine::KeyCode::eKEY_D:
      {
        HoverOverTile(x + 1,
                      y);
        break;
      }
      default:
      {
        break;
      }
    }
  }

  return nullptr;
}

/******************************************************************************/
void DefaultBoardInputState::HoverOverTile(int aXPos,
                                           int aYPos)
{
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layout = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    if(layout != nullptr)
    {
      // If a tile exists at the given location, set that tile to hovered.
      auto newTile = layout->GetTileAtPosition(aXPos,
                                               aYPos);
      if(newTile != nullptr)
      {
        int x = GetPlayerXLocation();
        int y = GetPlayerYLocation();

        // Un-hover the tile at the current location.
        auto oldTile = layout->GetTileAtPosition(x,
                                                 y);
        auto oldTileComp = oldTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(oldTileComp != nullptr)
        {
          oldTileComp->SetHovered(false);
        }

        // Set the hovered property of the tile at the new location.
        auto newTileComp = newTile->GetFirstComponentOfType<TileBehaviorComponent>();
        newTileComp->SetHovered(true);

        // Finally, update the player position.
        SetPlayerXLocation(aXPos);
        SetPlayerYLocation(aYPos);
      }
    }
  }
}
