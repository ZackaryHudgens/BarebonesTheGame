#include "MenuFactory.hpp"

#include <Environment.hpp>
#include <Scene.hpp>

#include "MainMenuInputComponent.hpp"
#include "MainMenuLayoutComponent.hpp"
#include "SkillMenuInputComponent.hpp"
#include "SkillMenuLayoutComponent.hpp"

#include "MenuAction.hpp"

#include "SceneFactory.hpp"

using Barebones::MenuFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> MenuFactory::CreateMenu(const MenuType& aType,
                                                                  const std::string& aName)
{
  auto newMenu = std::make_unique<UrsineEngine::GameObject>(aName);
  switch(aType)
  {
    case MenuType::eMAIN:
    {
      newMenu->AddComponent(std::make_unique<MainMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<MainMenuLayoutComponent>());

      // Add the start action.
      newMenu->GetFirstComponentOfType<MenuLayoutComponent>()->AddAction(std::make_unique<MenuAction>("Start Game"));
      auto startAction = newMenu->GetFirstComponentOfType<MenuLayoutComponent>()->GetActions().back();

      auto startFunction = []()
      {
        env.LoadScene(SceneFactory::CreateScene(SceneType::eBOARD));
      };
      startAction->SetFunction(startFunction);

      // Add the options action.
      newMenu->GetFirstComponentOfType<MenuLayoutComponent>()->AddAction(std::make_unique<MenuAction>("Options"));
      auto optionsAction = newMenu->GetFirstComponentOfType<MenuLayoutComponent>()->GetActions().back();

      auto optionsFunction = [aName]()
      {
        auto scene = env.GetCurrentScene();
        if(scene != nullptr)
        {
          auto menuObject = scene->GetObject(aName);
          if(menuObject != nullptr)
          {
            menuObject->ScheduleForDeletion();
          }

          auto newMenu = MenuFactory::CreateMenu(MenuType::eMAIN, "optionsMenu");
          scene->AddObject(std::move(newMenu));
        }
      };
      optionsAction->SetFunction(optionsFunction);

      // Add the exit action.
      newMenu->GetFirstComponentOfType<MenuLayoutComponent>()->AddAction(std::make_unique<MenuAction>("Exit"));
      auto exitAction = newMenu->GetFirstComponentOfType<MenuLayoutComponent>()->GetActions().back();

      auto exitFunction = []()
      {
        env.Exit();
      };
      exitAction->SetFunction(exitFunction);

      break;
    }
    case MenuType::eOPTIONS:
    {
      break;
    }
    case MenuType::eSKILL:
    {
      newMenu->AddComponent(std::make_unique<SkillMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<SkillMenuLayoutComponent>());

      break;
    }
    default:
    {
      break;
    }
  }

  return newMenu;
}
