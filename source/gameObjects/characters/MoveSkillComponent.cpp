#include "MoveSkillComponent.hpp"

#include <SpriteComponent.hpp>

using Barebones::MoveSkillComponent;

/******************************************************************************/
MoveSkillComponent::MoveSkillComponent()
  : CharacterSkillComponent()
{
  SetName("Move");
  SetDescription("Moves the character.");
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::MeshComponent> MoveSkillComponent::GetIcon()
{
  auto icon = std::make_unique<UrsineEngine::SpriteComponent>();

  // Create the texture.
  UrsineEngine::Texture sprite;
  sprite.CreateTextureFromFile("resources/sprites/menuBox.png");
  icon->SetTexture(sprite);

  // Create the shader.
  std::string vertexFile = "resources/shaders/UIShader.vert";
  std::string fragmentFile = "resources/shaders/UIShader.frag";
  UrsineEngine::Shader shader(vertexFile,
                              fragmentFile);
  icon->AddShader("uiShader",
                  shader);
  icon->SetCurrentShader("uiShader");

  // Display the icon in screen space.
  icon->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

  return icon;
}

/******************************************************************************/
void MoveSkillComponent::ProtectedSelect()
{
}

/******************************************************************************/
void MoveSkillComponent::ProtectedExecute()
{
}
