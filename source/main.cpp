#include <Environment.hpp>
#include <TextComponent.hpp>

#include "BoardFactory.hpp"

#include "CameraBehaviorComponent.hpp"
#include "CharacterFactory.hpp"
#include "CharacterBehaviorComponent.hpp"
#include "BoardLayoutComponent.hpp"
#include "BoardTurnManagerComponent.hpp"

#include "InputManagerComponent.hpp"

#include "PlayerFactory.hpp"

#include "BackgroundSpriteComponent.hpp"

int main()
{
  UrsineEngine::GraphicsOptions options;
  options.mCursorMode = UrsineEngine::CursorMode::eNORMAL;
  options.mTitle = "Barebones";
  options.mHeight = 720;
  options.mWidth = 1280;
  options.mOverlayHeight = 1080;
  options.mOverlayWidth = 1920;

  env.Initialize(options);

  UrsineEngine::TextComponent::LoadFont("resources/alagard.ttf");

  auto inputManager = std::make_unique<UrsineEngine::GameObject>("inputManager");
  inputManager->AddComponent(std::make_unique<Barebones::InputManagerComponent>());

  auto background = std::make_unique<UrsineEngine::GameObject>("background");
  background->AddComponent(std::make_unique<Barebones::BackgroundSpriteComponent>());

  auto board = Barebones::BoardFactory::CreateBoard("board");
  auto boardComp = board->GetFirstComponentOfType<Barebones::BoardLayoutComponent>();
  auto turnManager = board->GetFirstComponentOfType<Barebones::BoardTurnManagerComponent>();
  turnManager->AddPlayer(Barebones::PlayerFactory::CreatePlayer(Barebones::PlayerType::eARTIFICIAL, "artificialPlayer"));
  turnManager->AddPlayer(Barebones::PlayerFactory::CreatePlayer(Barebones::PlayerType::eHUMAN, "humanPlayer"));

  auto skeleton = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton");
  auto skeleton2 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton2");
  auto skeleton3 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton3");
  auto skeleton4 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton4");
  auto skeleton5 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton5");
  auto skeleton6 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton6");
  auto skeleton7 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton7");

  auto human = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_HUMAN, "human");
  auto human2 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_HUMAN, "human2");
  auto human3 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_HUMAN, "human3");
  auto human4 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_HUMAN, "human4");
  auto human5 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_HUMAN, "human5");
  auto human6 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_HUMAN, "human6");
  auto human7 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_HUMAN, "human7");

  boardComp->AddCharacterAtLocation(std::move(skeleton), Barebones::TileLocation(0, 0));
  boardComp->AddCharacterAtLocation(std::move(skeleton2), Barebones::TileLocation(0, 1));
  boardComp->AddCharacterAtLocation(std::move(skeleton3), Barebones::TileLocation(0, 2));
  boardComp->AddCharacterAtLocation(std::move(skeleton4), Barebones::TileLocation(0, 3));
  boardComp->AddCharacterAtLocation(std::move(skeleton5), Barebones::TileLocation(0, 4));
  boardComp->AddCharacterAtLocation(std::move(skeleton6), Barebones::TileLocation(0, 5));
  boardComp->AddCharacterAtLocation(std::move(skeleton7), Barebones::TileLocation(0, 6));

  boardComp->AddCharacterAtLocation(std::move(human), Barebones::TileLocation(6, 0));
  boardComp->AddCharacterAtLocation(std::move(human2), Barebones::TileLocation(6, 1));
  boardComp->AddCharacterAtLocation(std::move(human3), Barebones::TileLocation(6, 2));
  boardComp->AddCharacterAtLocation(std::move(human4), Barebones::TileLocation(6, 3));
  boardComp->AddCharacterAtLocation(std::move(human5), Barebones::TileLocation(6, 4));
  boardComp->AddCharacterAtLocation(std::move(human6), Barebones::TileLocation(6, 5));
  boardComp->AddCharacterAtLocation(std::move(human7), Barebones::TileLocation(6, 6));

  UrsineEngine::Scene newScene;

  newScene.AddObject(std::move(inputManager));
  newScene.GetBackground()->AddChild(std::move(background));

  auto cam = newScene.GetDefaultCamera();
  cam->AddComponent(std::make_unique<Barebones::CameraBehaviorComponent>());

  newScene.AddObject(std::move(board));

  auto camComp = cam->GetFirstComponentOfType<Barebones::CameraBehaviorComponent>();
  camComp->FollowBoard(*newScene.GetObject("board"));

  env.LoadScene(newScene);

  env.Run();

  return 0;
}
