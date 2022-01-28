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

  boardComp->AddCharacterAtPosition(std::move(skeleton), 0, 0);
  boardComp->AddCharacterAtPosition(std::move(skeleton2), 0, 1);
  boardComp->AddCharacterAtPosition(std::move(skeleton3), 0, 2);
  boardComp->AddCharacterAtPosition(std::move(skeleton4), 4, 6);
  boardComp->AddCharacterAtPosition(std::move(skeleton5), 0, 4);
  boardComp->AddCharacterAtPosition(std::move(skeleton6), 0, 5);
  boardComp->AddCharacterAtPosition(std::move(skeleton7), 0, 6);

  UrsineEngine::Scene newScene;

  auto cam = newScene.GetDefaultCamera();
  cam->AddComponent(std::make_unique<Barebones::CameraBehaviorComponent>());
  auto camComp = cam->GetFirstComponentOfType<Barebones::CameraBehaviorComponent>();

  newScene.AddObject(std::move(board));

  auto fpsObject = std::make_unique<UrsineEngine::GameObject>("fpsDisplay");
  fpsObject->AddComponent(std::make_unique<Barebones::FPSDisplay>());
  newScene.AddObject(std::move(fpsObject));

  env.LoadScene(newScene);

  env.Run();

  return 0;
}
