#include "SlowEffect.hpp"

#include <SpriteComponent.hpp>

using Barebones::SlowEffect;

/******************************************************************************/
SlowEffect::SlowEffect()
  : Effect()
{
  SetName("Slow");
  SetDescription("This character's speed is reduced.");
  SetStatusMessage("Slowed!");
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::MeshComponent> SlowEffect::GetIcon() const
{
  auto sprite = std::make_unique<UrsineEngine::SpriteComponent>();

  UrsineEngine::Texture texture;
  texture.CreateTextureFromFile("resources/sprites/fireballSpellSprite.png");
  sprite->SetTexture(texture);

  std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
  std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
  UrsineEngine::Shader shader(vertexFile, fragmentFile);
  sprite->AddShader("default", shader);
  sprite->SetCurrentShader("default");

  return std::move(sprite);
}
