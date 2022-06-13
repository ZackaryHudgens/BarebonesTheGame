#include "SceneFactory.hpp"

#include "BoardFactory.hpp"
#include "CharacterFactory.hpp"
#include "MenuFactory.hpp"
#include "PlayerFactory.hpp"

#include "BoardLayoutComponent.hpp"
#include "BoardTurnManagerComponent.hpp"

#include "InputManagerComponent.hpp"
#include "MenuManagerComponent.hpp"

#include "CameraBehaviorComponent.hpp"

#include "InfoPanelBehaviorComponent.hpp"

#include "BackgroundMeshComponent.hpp"

using Barebones::SceneFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::Scene> SceneFactory::CreateScene(const SceneType& aType)
{
  auto newScene = std::make_unique<UrsineEngine::Scene>();

  // Create an InputManager.
  auto inputManagerObject = std::make_unique<UrsineEngine::GameObject>("inputManager");
  inputManagerObject->AddComponent(std::make_unique<InputManagerComponent>());
  newScene->AddObject(std::move(inputManagerObject));

  // Create a MenuManager;
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
    case SceneType::eBOARD:
    {
      // Create a board.
      auto board = BoardFactory::CreateBoard("board");
      auto boardLayoutComponent = board->GetFirstComponentOfType<BoardLayoutComponent>();
      auto boardTurnManagerComponent = board->GetFirstComponentOfType<BoardTurnManagerComponent>();

      boardLayoutComponent->AddCharacterAtLocation(CharacterFactory::CreateCharacter(CharacterType::eCORRUPTED_FARMER, "human"),
                                                   TileLocation(5, 0));

      // Add a human player and an artificial player to the turn manager.
      boardTurnManagerComponent->AddPlayer(PlayerFactory::CreatePlayer(PlayerType::eHUMAN, "Player"));
      boardTurnManagerComponent->AddPlayer(PlayerFactory::CreatePlayer(PlayerType::eARTIFICIAL, "Enemy"));

      // Create a background.
      auto backgroundObject = std::make_unique<UrsineEngine::GameObject>("background");
      backgroundObject->AddComponent(std::make_unique<Barebones::BackgroundMeshComponent>());

      // Add the background and board to the scene.
      newScene->GetBackground()->AddChild(std::move(backgroundObject));
      newScene->AddObject(std::move(board));

      // Add a CameraBehaviorComponent to the default camera, then make it
      // follow the board.
      newScene->GetDefaultCamera()->AddComponent(std::make_unique<CameraBehaviorComponent>());
      newScene->GetDefaultCamera()->GetFirstComponentOfType<CameraBehaviorComponent>()->SetFollowedBoard(*newScene->GetObjects().back());

      // Create an information panel, then make it follow the board.
      auto infoPanelObject = std::make_unique<UrsineEngine::GameObject>("infoPanel");
      auto infoPanelBehaviorComponent = std::make_unique<InfoPanelBehaviorComponent>();
      infoPanelBehaviorComponent->SetFollowedBoard(*newScene->GetObjects().back());
      infoPanelObject->AddComponent(std::move(infoPanelBehaviorComponent));
      newScene->AddObject(std::move(infoPanelObject));
      break;
    }
    default:
    {
      break;
    }
  }

  return std::move(newScene);
}
