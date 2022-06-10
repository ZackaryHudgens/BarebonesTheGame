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

      auto menuLayoutComponent = newMenu->GetFirstComponentOfType<MenuLayoutComponent>();

      // Add the start action.
      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("Start Game"));
      auto startAction = menuLayoutComponent->GetActions().back();

      auto startFunction = []()
      {
        env.LoadScene(SceneFactory::CreateScene(SceneType::eBOARD));
      };
      startAction->SetFunction(startFunction);

      // Add the options action.
      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("Options"));
      auto optionsAction = menuLayoutComponent->GetActions().back();

      auto optionsFunction = []()
      {
        auto scene = env.GetCurrentScene();
        if(scene != nullptr)
        {
          auto newMenu = MenuFactory::CreateMenu(MenuType::eOPTIONS, "optionsMenu");
          scene->AddObject(std::move(newMenu));
        }
      };
      optionsAction->SetFunction(optionsFunction);

      // Add the exit action.
      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("Exit"));
      auto exitAction = menuLayoutComponent->GetActions().back();

      auto exitFunction = []()
      {
        env.Exit();
      };
      exitAction->SetFunction(exitFunction);

      break;
    }
    case MenuType::eOPTIONS:
    {
      newMenu->AddComponent(std::make_unique<MainMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<MainMenuLayoutComponent>());

      auto menuLayoutComponent = newMenu->GetFirstComponentOfType<MenuLayoutComponent>();

      // Add the resolution action.
      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("Resolution"));
      auto resolutionAction = menuLayoutComponent->GetActions().back();

      auto resolutionFunction = []()
      {
        auto scene = env.GetCurrentScene();
        if(scene != nullptr)
        {
          auto newMenu = MenuFactory::CreateMenu(MenuType::eRESOLUTION, "resolutionMenu");
          scene->AddObject(std::move(newMenu));
        }
      };
      resolutionAction->SetFunction(resolutionFunction);

      // Add the window type action.
      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("Window Type"));
      auto windowTypeAction = menuLayoutComponent->GetActions().back();

      auto windowTypeFunction = []()
      {
        auto scene = env.GetCurrentScene();
        if(scene != nullptr)
        {
          auto newMenu = MenuFactory::CreateMenu(MenuType::eWINDOW_TYPE, "windowTypeMenu");
          scene->AddObject(std::move(newMenu));
        }
      };
      windowTypeAction->SetFunction(windowTypeFunction);

      break;
    }
    case MenuType::eRESOLUTION:
    {
      newMenu->AddComponent(std::make_unique<MainMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<MainMenuLayoutComponent>());

      auto menuLayoutComponent = newMenu->GetFirstComponentOfType<MenuLayoutComponent>();

      auto graphicsOptions = env.GetGraphicsOptions();

      // Add an action for each supported resolution.
      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("1280x720"));

      auto resolutionFunction = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWidth = 1280;
        newOptions.mHeight = 720;

        env.Initialize(newOptions);
      };
      menuLayoutComponent->GetActions().back()->SetFunction(resolutionFunction);

      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("1366x768"));

      auto resolutionFunction2 = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWidth = 1366;
        newOptions.mHeight = 768;

        env.Initialize(newOptions);
      };
      menuLayoutComponent->GetActions().back()->SetFunction(resolutionFunction2);

      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("1600x900"));

      auto resolutionFunction3 = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWidth = 1600;
        newOptions.mHeight = 900;

        env.Initialize(newOptions);
      };
      menuLayoutComponent->GetActions().back()->SetFunction(resolutionFunction3);

      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("1920x1080"));

      auto resolutionFunction4 = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWidth = 1920;
        newOptions.mHeight = 1080;

        env.Initialize(newOptions);
      };
      menuLayoutComponent->GetActions().back()->SetFunction(resolutionFunction4);

      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("1920x1200"));

      auto resolutionFunction5 = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWidth = 1920;
        newOptions.mHeight = 1200;

        env.Initialize(newOptions);
      };
      menuLayoutComponent->GetActions().back()->SetFunction(resolutionFunction5);

      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("2560x1440"));

      auto resolutionFunction6 = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWidth = 2560;
        newOptions.mHeight = 1440;

        env.Initialize(newOptions);
      };
      menuLayoutComponent->GetActions().back()->SetFunction(resolutionFunction6);

      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("3840x2160"));

      auto resolutionFunction7 = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWidth = 3840;
        newOptions.mHeight = 2160;

        env.Initialize(newOptions);
      };
      menuLayoutComponent->GetActions().back()->SetFunction(resolutionFunction7);

      break;
    }
    case MenuType::eWINDOW_TYPE:
    {
      newMenu->AddComponent(std::make_unique<MainMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<MainMenuLayoutComponent>());

      auto menuLayoutComponent = newMenu->GetFirstComponentOfType<MenuLayoutComponent>();

      auto graphicsOptions = env.GetGraphicsOptions();

      // Add the windowed option.
      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("Windowed"));
      if(graphicsOptions.mWindowMode == UrsineEngine::WindowMode::eWINDOWED)
      {
        menuLayoutComponent->GetActions().back()->SetEnabled(false);
      }

      auto windowedFunction = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWindowMode = UrsineEngine::WindowMode::eWINDOWED;

        env.Initialize(newOptions);
      };
      menuLayoutComponent->GetActions().back()->SetFunction(windowedFunction);

      // Add the fullscreen action.
      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("Fullscreen"));
      if(graphicsOptions.mWindowMode == UrsineEngine::WindowMode::eFULLSCREEN)
      {
        menuLayoutComponent->GetActions().back()->SetEnabled(false);
      }

      auto fullscreenFunction = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWindowMode = UrsineEngine::WindowMode::eFULLSCREEN;

        env.Initialize(newOptions);
      };
      menuLayoutComponent->GetActions().back()->SetFunction(fullscreenFunction);

      // Add the borderless action.
      menuLayoutComponent->AddAction(std::make_unique<MenuAction>("Borderless"));
      if(graphicsOptions.mWindowMode == UrsineEngine::WindowMode::eBORDERLESS_FULLSCREEN)
      {
        menuLayoutComponent->GetActions().back()->SetEnabled(false);
      }

      auto borderlessFunction = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWindowMode = UrsineEngine::WindowMode::eBORDERLESS_FULLSCREEN;

        env.Initialize(newOptions);
      };
      menuLayoutComponent->GetActions().back()->SetFunction(borderlessFunction);

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
