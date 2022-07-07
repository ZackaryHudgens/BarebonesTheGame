#include "SceneFactory.hpp"

#include "BoardFactory.hpp"
#include "CharacterFactory.hpp"
#include "MenuFactory.hpp"
#include "PlayerFactory.hpp"

#include "BoardTurnManagerComponent.hpp"
#include "BoardWaveManagerComponent.hpp"

#include "InputManagerComponent.hpp"
#include "MenuManagerComponent.hpp"

#include "CameraBehaviorComponent.hpp"

#include "ActDisplayBehaviorComponent.hpp"
#include "ActDisplayInputComponent.hpp"
#include "InfoPanelBehaviorComponent.hpp"
#include "HintDisplayBehaviorComponent.hpp"

#include "BackgroundMeshComponent.hpp"

#include "Fonts.hpp"

using Barebones::SceneFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::Scene> SceneFactory::CreateScene(const SceneType& aType)
{
  auto newScene = std::make_unique<UrsineEngine::Scene>();

  // Create an InputManager.
  auto inputManagerObject = std::make_unique<UrsineEngine::GameObject>("inputManager");
  inputManagerObject->AddComponent(std::make_unique<InputManagerComponent>());
  newScene->AddObject(std::move(inputManagerObject));

  // Create a MenuManager.
  auto menuManagerObject = std::make_unique<UrsineEngine::GameObject>("menuManager");
  menuManagerObject->AddComponent(std::make_unique<MenuManagerComponent>());
  newScene->AddObject(std::move(menuManagerObject));

  switch(aType)
  {
    case SceneType::eMAIN_MENU:
    {
      // Create a background.
      auto backgroundObject = std::make_unique<UrsineEngine::GameObject>("background");
      backgroundObject->AddComponent(std::make_unique<Barebones::BackgroundMeshComponent>());
      newScene->AddObject(std::move(backgroundObject));

      // Create the main menu.
      auto menu = MenuFactory::CreateMenu(MenuType::eMAIN, "mainMenu");
      newScene->AddObject(std::move(menu));

      break;
    }
    case SceneType::eBOARD_ACT_ONE:
    {
      AddBoardToScene(*newScene.get(), Act::eACT_ONE);
      break;
    }
    case SceneType::eBOARD_ACT_TWO:
    {
      AddBoardToScene(*newScene.get(), Act::eACT_TWO);
      break;
    }
    case SceneType::eBOARD_ACT_THREE:
    {
      AddBoardToScene(*newScene.get(), Act::eACT_THREE);
      break;
    }
    case SceneType::eBOARD_FINALE:
    {
      AddBoardToScene(*newScene.get(), Act::eFINALE);
      break;
    }
    default:
    {
      break;
    }
  }

  return std::move(newScene);
}

/******************************************************************************/
void SceneFactory::AddBoardToScene(UrsineEngine::Scene& aScene, const Act& aAct)
{
  // Create a board.
  auto board = BoardFactory::CreateBoard("board");
  auto boardTurnManagerComponent = board->GetFirstComponentOfType<BoardTurnManagerComponent>();
  auto boardWaveManagerComponent = board->GetFirstComponentOfType<BoardWaveManagerComponent>();

  // Add a human player and an artificial player to the turn manager.
  boardTurnManagerComponent->AddPlayer(PlayerFactory::CreatePlayer(PlayerType::eHUMAN, "Player"));
  boardTurnManagerComponent->AddPlayer(PlayerFactory::CreatePlayer(PlayerType::eARTIFICIAL, "Enemy"));

  // Set the act for the wave manager.
  boardWaveManagerComponent->SetAct(aAct);

  // Create a background.
  auto backgroundObject = std::make_unique<UrsineEngine::GameObject>("background");
  backgroundObject->AddComponent(std::make_unique<Barebones::BackgroundMeshComponent>());

  // Add the background and board to the scene.
  aScene.GetBackground()->AddChild(std::move(backgroundObject));
  aScene.AddObject(std::move(board));

  // Add a CameraBehaviorComponent to the default camera, then make it
  // follow the board.
  aScene.GetDefaultCamera()->AddComponent(std::make_unique<CameraBehaviorComponent>());
  aScene.GetDefaultCamera()->GetFirstComponentOfType<CameraBehaviorComponent>()->SetFollowedBoard(*aScene.GetObjects().back());

  // Create an information panel, then make it follow the board.
  auto infoPanelObject = std::make_unique<UrsineEngine::GameObject>("infoPanel");
  auto infoPanelBehaviorComponent = std::make_unique<InfoPanelBehaviorComponent>();
  infoPanelBehaviorComponent->SetFollowedBoard(*aScene.GetObjects().back());
  infoPanelObject->AddComponent(std::move(infoPanelBehaviorComponent));
  aScene.AddObject(std::move(infoPanelObject));

  // Create the act display.
  auto actDisplayObject = std::make_unique<UrsineEngine::GameObject>("actDisplay");
  actDisplayObject->AddComponent(std::make_unique<ActDisplayBehaviorComponent>());
  actDisplayObject->AddComponent(std::make_unique<ActDisplayInputComponent>());

  actDisplayObject->GetFirstComponentOfType<ActDisplayBehaviorComponent>()->DisplayTextForAct(aAct);

  aScene.AddObject(std::move(actDisplayObject));

  // Create the hint display.
  auto hintDisplayObject = std::make_unique<UrsineEngine::GameObject>("hintDisplay");
  hintDisplayObject->AddComponent(std::make_unique<HintDisplayBehaviorComponent>());
  aScene.AddObject(std::move(hintDisplayObject));
}
