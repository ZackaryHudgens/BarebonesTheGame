#include "TestEffect.hpp"

#include <SpriteComponent.hpp>

using Barebones::TestEffect;

/******************************************************************************/
TestEffect::TestEffect()
  : Effect()
{
  SetName("woo");
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::MeshComponent> TestEffect::GetIcon() const
{
  auto sprite = std::make_unique<UrsineEngine::SpriteComponent>();

  UrsineEngine::Texture texture;
  texture.CreateTextureFromFile("resources/sprites/basicBrick.png");
  sprite->SetTexture(texture);

  std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
  std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
  UrsineEngine::Shader shader(vertexFile, fragmentFile);
  sprite->AddShader("default", shader);
  sprite->SetCurrentShader("default");

  return std::move(sprite);
}
