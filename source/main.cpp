#include <Environment.hpp>
#include <TextComponent.hpp>

#include "SceneFactory.hpp"

int main()
{
  UrsineEngine::GraphicsOptions options;
  options.mCursorMode = UrsineEngine::CursorMode::eNORMAL;
  options.mTitle = "Barebones";
  options.mHeight = 720;
  options.mWidth = 1280;
  options.mOverlayHeight = 1080;
  options.mOverlayWidth = 1920;

  UrsineEngine::TextComponent::LoadFont("resources/alagard.ttf");

  env.Initialize(options);
  env.LoadScene(Barebones::SceneFactory::CreateScene(Barebones::SceneType::eBOARD));
  env.Run();

  return 0;
}
