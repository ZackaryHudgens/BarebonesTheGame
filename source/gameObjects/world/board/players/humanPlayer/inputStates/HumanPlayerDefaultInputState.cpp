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
  : HumanPlayerMovableInputState(aPlayer)
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
      auto currentLocation = boardLayoutComponent->GetFocusedTileLocation();
      switch(aCode)
      {
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
        case UrsineEngine::KeyCode::eKEY_Q:
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
          newState = HumanPlayerMovableInputState::HandleKeyPressed(aCode, aMods);
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
    case UrsineEngine::KeyCode::eKEY_ENTER:
    case UrsineEngine::KeyCode::eKEY_Q:
    {
      break;
    }
    default:
    {
      newState = HumanPlayerMovableInputState::HandleKeyRepeated(aCode, aMods);
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
  auto menuLayoutComponent = aMenu.GetFirstComponentOfType<MenuLayoutComponent>();
  if(boardObject != nullptr &&
     menuLayoutComponent != nullptr)
  {
    auto boardLayoutComponent = boardObject->GetFirstComponentOfType<BoardLayoutComponent>();
    if(boardLayoutComponent != nullptr)
    {
      auto currentLocation = boardLayoutComponent->GetFocusedTileLocation();

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

