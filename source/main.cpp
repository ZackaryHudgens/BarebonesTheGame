#include <time.h>

#include <Environment.hpp>
#include <TextComponent.hpp>
#include <AudioComponent.hpp>

#include "SceneFactory.hpp"

int main()
{
  std::srand(time(0));

  UrsineEngine::GraphicsOptions options;
  options.mCursorMode = UrsineEngine::CursorMode::eNORMAL;
  options.mTitle = "Barebones";
  options.mHeight = 720;
  options.mWidth = 1280;
  options.mOverlayHeight = 1080;
  options.mOverlayWidth = 1920;

  UrsineEngine::TextComponent::InitializeFontLibrary();
  UrsineEngine::TextComponent::LoadFont("resources/alagard.ttf");

  UrsineEngine::AudioComponent::InitializeAudioLibrary();
  UrsineEngine::AudioComponent::LoadAudioFile("resources/audio/arrowMoved.wav");
  UrsineEngine::AudioComponent::SetSoundVolume("resources/audio/arrowMoved.wav", 0.1);

  env.Initialize(options);
  env.LoadScene(Barebones::SceneFactory::CreateScene(Barebones::SceneType::eMAIN_MENU));
  env.Run();

  UrsineEngine::TextComponent::UninitializeFontLibrary();
  UrsineEngine::AudioComponent::UninitializeAudioLibrary();

  return 0;
}
