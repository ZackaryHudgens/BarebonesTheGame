#include "SlowEffect.hpp"

#include <SpriteComponent.hpp>

#include "CharacterBehaviorComponent.hpp"

using Barebones::SlowEffect;

/******************************************************************************/
SlowEffect::SlowEffect()
  : Effect()
  , mCharacterSpeed(0)
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
  texture.CreateTextureFromFile("resources/sprites/effects/slow.png");
  sprite->SetTexture(texture);

  std::string vertexFile = "resources/shaders/TexturedMeshShader.vert";
  std::string fragmentFile = "resources/shaders/TexturedMeshShader.frag";
  UrsineEngine::Shader shader(vertexFile, fragmentFile);
  sprite->AddShader("default", shader);
  sprite->SetCurrentShader("default");

  return std::move(sprite);
}

/******************************************************************************/
void SlowEffect::HandleAddedToCharacter(CharacterBehaviorComponent& aCharacter)
{
  mCharacterSpeed = aCharacter.GetSpeed();
  aCharacter.SetSpeed(mCharacterSpeed - 1);
}

/******************************************************************************/
void SlowEffect::HandleRemovedFromCharacter(CharacterBehaviorComponent& aCharacter)
{
  aCharacter.SetSpeed(mCharacterSpeed);
}
