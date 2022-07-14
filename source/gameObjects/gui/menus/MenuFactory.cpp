#include "MenuFactory.hpp"

#include <Environment.hpp>
#include <Scene.hpp>

#include "BasicMenuLayoutComponent.hpp"
#include "BasicMenuInputComponent.hpp"
#include "BasicMenuAudioComponent.hpp"
#include "SkillMenuInputComponent.hpp"
#include "SkillMenuLayoutComponent.hpp"
#include "RewardsMenuInputComponent.hpp"
#include "RewardsMenuLayoutComponent.hpp"

#include "MenuAction.hpp"

#include "SceneFactory.hpp"

#include "Signals.hpp"

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
      newMenu->AddComponent(std::make_unique<BasicMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuLayoutComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuAudioComponent>());

      auto menuLayoutComponent = newMenu->GetFirstComponentOfType<MenuLayoutComponent>();

      // Add the start action.
      auto startAction = std::make_unique<MenuAction>("Start Game");
      auto startFunction = []()
      {
        ScreenTransitionRequested.Notify(SceneType::eBOARD_ACT_ONE);
      };
      startAction->SetFunction(startFunction);
      menuLayoutComponent->AddAction(std::move(startAction));

      // Add the options action.
      auto optionsAction = std::make_unique<MenuAction>("Options");
      auto optionsFunction = []()
      {
      };
      optionsAction->SetFunction(optionsFunction);
      menuLayoutComponent->AddAction(std::move(optionsAction));

      // Add the exit action.
      auto exitAction = std::make_unique<MenuAction>("Exit");
      auto exitFunction = []()
      {
        env.Exit();
      };
      exitAction->SetFunction(exitFunction);
      menuLayoutComponent->AddAction(std::move(exitAction));

      break;
    }
    case MenuType::eOPTIONS:
    {
      newMenu->AddComponent(std::make_unique<BasicMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuLayoutComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuAudioComponent>());

      auto menuLayoutComponent = newMenu->GetFirstComponentOfType<MenuLayoutComponent>();

      // Add the resolution action.
      auto resolutionAction = std::make_unique<MenuAction>("Resolution");
      auto resolutionFunction = []()
      {
      };
      resolutionAction->SetFunction(resolutionFunction);
      menuLayoutComponent->AddAction(std::move(resolutionAction));

      // Add the window type action.
      auto windowTypeAction = std::make_unique<MenuAction>("Window Type");
      auto windowTypeFunction = []()
      {
      };
      windowTypeAction->SetFunction(windowTypeFunction);
      menuLayoutComponent->AddAction(std::move(windowTypeAction));

      break;
    }
    case MenuType::eRESOLUTION:
    {
      newMenu->AddComponent(std::make_unique<BasicMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuLayoutComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuAudioComponent>());

      auto menuLayoutComponent = newMenu->GetFirstComponentOfType<MenuLayoutComponent>();

      break;
    }
    case MenuType::eWINDOW_TYPE:
    {
      newMenu->AddComponent(std::make_unique<BasicMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuLayoutComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuAudioComponent>());

      auto menuLayoutComponent = newMenu->GetFirstComponentOfType<MenuLayoutComponent>();

      auto graphicsOptions = env.GetGraphicsOptions();

      // Add the windowed action.
      auto windowedAction = std::make_unique<MenuAction>("Windowed");
      auto windowedFunction = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWindowMode = UrsineEngine::WindowMode::eWINDOWED;

        env.Initialize(newOptions);
      };
      windowedAction->SetFunction(windowedFunction);
      menuLayoutComponent->AddAction(std::move(windowedAction));

      // Add the fullscreen action.
      auto fullscreenAction = std::make_unique<MenuAction>("Fullscreen");
      auto fullscreenFunction = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWindowMode = UrsineEngine::WindowMode::eFULLSCREEN;

        env.Initialize(newOptions);
      };
      windowedAction->SetFunction(fullscreenFunction);
      menuLayoutComponent->AddAction(std::move(fullscreenAction));

      // Add the borderless fullscreen action.
      auto borderlessAction = std::make_unique<MenuAction>("Borderless");
      auto borderlessFunction = [graphicsOptions]()
      {
        UrsineEngine::GraphicsOptions newOptions = graphicsOptions;
        newOptions.mWindowMode = UrsineEngine::WindowMode::eBORDERLESS_FULLSCREEN;

        env.Initialize(newOptions);
      };
      borderlessAction->SetFunction(borderlessFunction);
      menuLayoutComponent->AddAction(std::move(borderlessAction));

      break;
    }
    case MenuType::ePAUSE:
    {
      newMenu->AddComponent(std::make_unique<BasicMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuLayoutComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuAudioComponent>());

      auto menuLayoutComponent = newMenu->GetFirstComponentOfType<MenuLayoutComponent>();

      // Add the resume action.
      auto resumeAction = std::make_unique<MenuAction>("Resume");
      auto resumeFunction = [menuLayoutComponent]()
      {
        auto parent = menuLayoutComponent->GetParent();
        if(parent != nullptr)
        {
          parent->ScheduleForDeletion();
        }
      };
      resumeAction->SetFunction(resumeFunction);
      menuLayoutComponent->AddAction(std::move(resumeAction));

      // Add the options action.
      auto optionsAction = std::make_unique<MenuAction>("Options");
      auto optionsFunction = []()
      {
      };
      optionsAction->SetFunction(optionsFunction);
      menuLayoutComponent->AddAction(std::move(optionsAction));

      // Add the exit action.
      auto exitAction = std::make_unique<MenuAction>("Exit to Title");
      auto exitFunction = []()
      {
        ScreenTransitionRequested.Notify(SceneType::eMAIN_MENU);
      };
      exitAction->SetFunction(exitFunction);
      menuLayoutComponent->AddAction(std::move(exitAction));

      break;
    }
    case MenuType::eSKILL:
    {
      newMenu->AddComponent(std::make_unique<SkillMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<SkillMenuLayoutComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuAudioComponent>());

      break;
    }
    case MenuType::eREWARDS:
    {
      newMenu->AddComponent(std::make_unique<RewardsMenuLayoutComponent>());
      newMenu->AddComponent(std::make_unique<RewardsMenuInputComponent>());
      newMenu->AddComponent(std::make_unique<BasicMenuAudioComponent>());

      break;
    }
    default:
    {
      break;
    }
  }

  return newMenu;
}
