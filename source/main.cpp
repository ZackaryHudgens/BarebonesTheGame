#include <Environment.hpp>

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

  UrsineEngine::Scene newScene;
  newScene.AddObject(std::move(board));

  auto cam = newScene.GetDefaultCamera();
  cam->SetPosition(glm::vec3(2.0, 7.0, 10.0));
  cam->SetRotation(-50, glm::vec3(1.0, 0.0, 0.0));

  env.LoadScene(newScene);

  env.Run();

  return 0;
}
