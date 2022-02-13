#include "DefendSkillComponent.hpp"

#include <SpriteComponent.hpp>

using Barebones::DefendSkillComponent;

/******************************************************************************/
DefendSkillComponent::DefendSkillComponent()
  : CharacterSkillComponent()
{
  SetName("Defend");
  SetDescription("What a wuss.");
  SetHighlightColor(glm::vec3(1.0,
                              1.0,
                              0.0));
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::MeshComponent> DefendSkillComponent::GetIcon()
{
  auto icon = std::make_unique<UrsineEngine::SpriteComponent>();

  // Create the texture.
  UrsineEngine::Texture sprite;
  sprite.CreateTextureFromFile("resources/sprites/menuBox.png");
  icon->SetTexture(sprite);

  // Create the shader.
  std::string vertexFile = "resources/shaders/UIShader.vert";
  std::string fragmentFile = "resources/shaders/SkillActionShader.frag";
  UrsineEngine::Shader shader(vertexFile,
                              fragmentFile);

  // Initialize the glow color.
  shader.Activate();
  shader.SetVec4("glowColor",
                 glm::vec4(1.0,
                           1.0,
                           1.0,
                           1.0));
  icon->AddShader("defaultShader",
                  shader);
  icon->SetCurrentShader("defaultShader");

  // Display the icon in screen space.
  icon->SetCoordinateSystem(UrsineEngine::CoordinateSystem::eSCREEN_SPACE);

  return icon;
}

/******************************************************************************/
Barebones::TileList DefendSkillComponent::GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                                              const TileLocation& aLocation)
{
  return TileList();
}

/******************************************************************************/
bool DefendSkillComponent::IsTileValid(UrsineEngine::GameObject& aBoard,
                                       const TileLocation& aLocation)
{
  return true;
}

/******************************************************************************/
void DefendSkillComponent::ProtectedSelect()
{
}

/******************************************************************************/
void DefendSkillComponent::ProtectedExecute(UrsineEngine::GameObject& aBoard,
                                            const TileLocation& aLocation)
{
}
