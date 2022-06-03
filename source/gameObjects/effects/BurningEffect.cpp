#include "BurningEffect.hpp"

#include <SpriteComponent.hpp>

using Barebones::BurningEffect;

/******************************************************************************/
BurningEffect::BurningEffect()
  : Effect()
{
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::MeshComponent> BurningEffect::GetIcon() const
{
  auto sprite = std::make_unique<UrsineEngine::SpriteComponent>();

  UrsineEngine::Texture texture;
  texture.CreateTextureFromFile("resources/sprites/effects/fireballSpellSprite.png");
  sprite->SetTexture(texture);

  std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
  std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
  UrsineEngine::Shader shader(vertexFile, fragmentFile);
  sprite->AddShader("default", shader);
  sprite->SetCurrentShader("default");

  return std::move(sprite);
}
