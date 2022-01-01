#include <Environment.hpp>

int main()
{
  UrsineEngine::GraphicsOptions options;
  options.mCursorMode = UrsineEngine::CursorMode::eNORMAL;
  options.mTitle = "Barebones";
  options.mHeight = 720;
  options.mWidth = 1280;

  env.Initialize(options);

  UrsineEngine::Scene newScene;
  env.LoadScene(newScene);

  env.Run();

  return 0;
}
