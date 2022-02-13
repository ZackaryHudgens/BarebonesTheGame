#include "DefaultBoardInputState.hpp"

#include <Environment.hpp>

#include "UsingSkillBoardInputState.hpp"

#include "ActionFactory.hpp"
#include "MenuFactory.hpp"
#include "MenuLayoutComponent.hpp"
#include "SkillActionBehaviorComponent.hpp"

#include "BoardInputComponent.hpp"

#include "TileBehaviorComponent.hpp"

#include "CharacterSkillComponent.hpp"

#include <iostream>

using Barebones::DefaultBoardInputState;

/******************************************************************************/
DefaultBoardInputState::DefaultBoardInputState(UrsineEngine::GameObject& aObject)
  : BoardInputState(aObject)
{
  // Upon entering this state, hover over the tile at the player's location.
  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layoutComponent = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
    if(layoutComponent != nullptr &&
       inputComponent != nullptr)
    {
      auto newTile = layoutComponent->GetTileAtLocation(inputComponent->GetPlayerLocation());
      if(newTile != nullptr)
      {
        auto newTileBehaviorComp = newTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(newTileBehaviorComp != nullptr)
        {
          newTileBehaviorComp->SetHovered(true);
        }
      }
    }
  }
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> DefaultBoardInputState::HandleKeyPressed(const UrsineEngine::KeyCode& aCode,
                                                                                     int aMods)
{
  std::unique_ptr<Barebones::BoardInputState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
    if(inputComponent != nullptr)
    {
      auto currentLocation = inputComponent->GetPlayerLocation();

      switch(aCode)
      {
        case UrsineEngine::KeyCode::eKEY_UP:
        case UrsineEngine::KeyCode::eKEY_W:
        {
          inputComponent->SetPlayerLocation(TileLocation(currentLocation.first,
                                                         currentLocation.second + 1));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_DOWN:
        case UrsineEngine::KeyCode::eKEY_S:
        {
          inputComponent->SetPlayerLocation(TileLocation(currentLocation.first,
                                                         currentLocation.second - 1));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_LEFT:
        case UrsineEngine::KeyCode::eKEY_A:
        {
          inputComponent->SetPlayerLocation(TileLocation(currentLocation.first - 1,
                                                         currentLocation.second));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_RIGHT:
        case UrsineEngine::KeyCode::eKEY_D:
        {
          inputComponent->SetPlayerLocation(TileLocation(currentLocation.first + 1,
                                                         currentLocation.second));
          break;
        }
        case UrsineEngine::KeyCode::eKEY_ENTER:
        {
          // If there is a character at the player's current location,
          // then create a menu containing all of that character's
          // available skills.
          auto parent = GetParent();
          if(parent != nullptr)
          {
            auto layout = parent->GetFirstComponentOfType<BoardLayoutComponent>();
            if(layout != nullptr)
            {
              auto character = layout->GetCharacterAtLocation(currentLocation);
              if(character != nullptr)
              {
                CreateSkillMenu(*character);
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
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> DefaultBoardInputState::HandleKeyRepeated(const UrsineEngine::KeyCode& aCode,
                                                                                      int aMods)
{
  std::unique_ptr<Barebones::BoardInputState> newState = nullptr;

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
std::unique_ptr<Barebones::BoardInputState> DefaultBoardInputState::HandlePlayerMoved(const TileLocation& aPrevLocation,
                                                                                      const TileLocation& aNewLocation)
{
  std::unique_ptr<BoardInputState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto layoutComponent = parent->GetFirstComponentOfType<BoardLayoutComponent>();
    if(layoutComponent != nullptr)
    {
      // Un-hover the tile at the previous location.
      auto prevTile = layoutComponent->GetTileAtLocation(aPrevLocation);
      if(prevTile != nullptr)
      {
        auto prevTileBehaviorComp = prevTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(prevTileBehaviorComp != nullptr)
        {
          prevTileBehaviorComp->SetHovered(false);
        }
      }

      // Hover over the tile at the new location.
      auto newTile = layoutComponent->GetTileAtLocation(aNewLocation);
      if(newTile != nullptr)
      {
        auto newTileBehaviorComp = newTile->GetFirstComponentOfType<TileBehaviorComponent>();
        if(newTileBehaviorComp != nullptr)
        {
          auto inputComponent = parent->GetFirstComponentOfType<BoardInputComponent>();
          if(inputComponent != nullptr)
          {
            newTileBehaviorComp->SetHovered(true);
          }
        }
      }
    }
  }

  return newState;
}

/******************************************************************************/
std::unique_ptr<Barebones::BoardInputState> DefaultBoardInputState::HandleSkillSelected(CharacterSkillComponent& aSkill)
{
  // When a skill is selected, switch to the Using Skill state.
  std::unique_ptr<BoardInputState> newState = nullptr;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    newState = std::make_unique<UsingSkillBoardInputState>(*parent,
                                                           aSkill);
  }

  return newState;
}

/******************************************************************************/
void DefaultBoardInputState::CreateSkillMenu(UrsineEngine::GameObject& aObject)
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
