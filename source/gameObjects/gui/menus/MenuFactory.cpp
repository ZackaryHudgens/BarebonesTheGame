#include "MenuFactory.hpp"

#include <Environment.hpp>
#include <Scene.hpp>

#include "MainMenuInputComponent.hpp"
#include "MainMenuLayoutComponent.hpp"
#include "SkillMenuInputComponent.hpp"
#include "SkillMenuLayoutComponent.hpp"
#include "SpellMenuLayoutComponent.hpp"

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

      auto startAction = std::make_unique<MenuAction>("Start Game");
      auto startGameFunction = []()
      {
        env.LoadScene(SceneFactory::CreateScene(SceneType::eBOARD));
      };
      startAction->SetFunction(startGameFunction);

      auto optionsAction = std::make_unique<MenuAction>("Options");
      auto quitAction = std::make_unique<MenuAction>("Quit");
      newMenu->GetFirstComponentOfType<MenuLayoutComponent>()->AddAction(std::move(startAction));
      newMenu->GetFirstComponentOfType<MenuLayoutComponent>()->AddAction(std::move(optionsAction));
      newMenu->GetFirstComponentOfType<MenuLayoutComponent>()->AddAction(std::move(quitAction));
      break;
    }
    case MenuType::eSKILL:
    {
      newMenu->AddComponent(std::make_unique<SkillMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<SkillMenuLayoutComponent>());
      break;
    }
    case MenuType::eSPELL:
    {
      newMenu->AddComponent(std::make_unique<SkillMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<SpellMenuLayoutComponent>());
      break;
    }
    default:
    {
      break;
    }
  }

  return newMenu;
}
