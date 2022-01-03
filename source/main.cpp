#include <Environment.hpp>

#include "TileObject.hpp"

int main()
{
  UrsineEngine::GraphicsOptions options;
  options.mCursorMode = UrsineEngine::CursorMode::eNORMAL;
  options.mTitle = "Barebones";
  options.mHeight = 720;
  options.mWidth = 1280;

  env.Initialize(options);

  auto tile = std::make_unique<Barebones::TileObject>("tile");
  tile->Translate(glm::vec3(0.0, 0.0, -5.0));

  UrsineEngine::Scene newScene;
  newScene.AddObject(std::move(tile));

  env.LoadScene(newScene);

  env.Run();

  return 0;
}
