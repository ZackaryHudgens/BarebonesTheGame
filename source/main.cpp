#include <Environment.hpp>

#include "CameraBehaviorComponent.hpp"
#include "CharacterFactory.hpp"
#include "BoardBehaviorComponent.hpp"

int main()
{
  UrsineEngine::GraphicsOptions options;
  options.mCursorMode = UrsineEngine::CursorMode::eNORMAL;
  options.mTitle = "Barebones";
  options.mHeight = 720;
  options.mWidth = 1280;

  env.Initialize(options);

  auto board = std::make_unique<UrsineEngine::GameObject>("board");
  board->AddComponent(std::make_unique<Barebones::BoardBehaviorComponent>());
  auto boardComp = board->GetFirstComponentOfType<Barebones::BoardBehaviorComponent>();

  auto skeleton = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton");
  auto skeleton2 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton2");
  auto skeleton3 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton3");
  auto skeleton4 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton4");
  auto skeleton5 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton5");
  auto skeleton6 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton6");
  auto skeleton7 = Barebones::CharacterFactory::CreateCharacter(Barebones::CharacterType::eBASIC_SKELETON, "skeleton7");

  boardComp->AddObjectAtPosition(std::move(skeleton), 0, 0);
  boardComp->AddObjectAtPosition(std::move(skeleton2), 0, 1);
  boardComp->AddObjectAtPosition(std::move(skeleton3), 0, 2);
  boardComp->AddObjectAtPosition(std::move(skeleton4), 0, 3);
  boardComp->AddObjectAtPosition(std::move(skeleton5), 0, 4);
  boardComp->AddObjectAtPosition(std::move(skeleton6), 0, 5);
  boardComp->AddObjectAtPosition(std::move(skeleton7), 0, 6);

  UrsineEngine::Scene newScene;

  auto cam = newScene.GetDefaultCamera();
  cam->AddComponent(std::make_unique<Barebones::CameraBehaviorComponent>());
  auto camComp = cam->GetFirstComponentOfType<Barebones::CameraBehaviorComponent>();
  camComp->FollowBoard(*board.get());

  newScene.AddObject(std::move(board));

  env.LoadScene(newScene);

  env.Run();

  return 0;
}
