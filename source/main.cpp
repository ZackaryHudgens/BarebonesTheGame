#include <Environment.hpp>

#include "CameraBehaviorComponent.hpp"
#include "CharacterFactory.hpp"
#include "CharacterBehaviorComponent.hpp"
#include "BoardInputComponent.hpp"
#include "BoardLayoutComponent.hpp"

#include "FPSDisplay.hpp"

#include <iostream>

int main()
{
  UrsineEngine::GraphicsOptions options;
  options.mCursorMode = UrsineEngine::CursorMode::eNORMAL;
  options.mTitle = "Barebones";
  options.mHeight = 720;
  options.mWidth = 1280;

  env.Initialize(options);

  auto board = std::make_unique<UrsineEngine::GameObject>("board");
  board->AddComponent(std::make_unique<Barebones::BoardLayoutComponent>());
  board->AddComponent(std::make_unique<Barebones::BoardInputComponent>());
  auto boardComp = board->GetFirstComponentOfType<Barebones::BoardLayoutComponent>();

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

  boardComp->AddCharacterAtPosition(std::move(skeleton), 0, 0);
  boardComp->AddCharacterAtPosition(std::move(skeleton2), 0, 1);
  boardComp->AddCharacterAtPosition(std::move(skeleton3), 0, 2);
  boardComp->AddCharacterAtPosition(std::move(skeleton4), 0, 3);
  boardComp->AddCharacterAtPosition(std::move(skeleton5), 0, 4);
  boardComp->AddCharacterAtPosition(std::move(skeleton6), 0, 5);
  boardComp->AddCharacterAtPosition(std::move(skeleton7), 0, 6);

  boardComp->AddCharacterAtPosition(std::move(human), 6, 0);
  boardComp->AddCharacterAtPosition(std::move(human2), 6, 1);
  boardComp->AddCharacterAtPosition(std::move(human3), 6, 2);
  boardComp->AddCharacterAtPosition(std::move(human4), 6, 3);
  boardComp->AddCharacterAtPosition(std::move(human5), 6, 4);
  boardComp->AddCharacterAtPosition(std::move(human6), 6, 5);
  boardComp->AddCharacterAtPosition(std::move(human7), 6, 6);

  UrsineEngine::Scene newScene;

  auto cam = newScene.GetDefaultCamera();
  cam->AddComponent(std::make_unique<Barebones::CameraBehaviorComponent>());
  auto camComp = cam->GetFirstComponentOfType<Barebones::CameraBehaviorComponent>();

  newScene.AddObject(std::move(board));

  env.LoadScene(newScene);

  env.Run();

  return 0;
}
