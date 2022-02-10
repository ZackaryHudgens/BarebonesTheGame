#include "MoveSkillComponent.hpp"

#include <algorithm>

#include <SpriteComponent.hpp>

#include "CharacterBehaviorComponent.hpp"

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
  sprite.CreateTextureFromFile("resources/sprites/bear.jpeg");
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
Barebones::TileList MoveSkillComponent::GetTilesToHighlight(UrsineEngine::GameObject& aBoard,
                                                            const TileLocation& aLocation)
{
  TileList tiles;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto behaviorComp = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(behaviorComp != nullptr)
    {
      tiles = behaviorComp->GetMovements(aBoard,
                                         aLocation);
    }
  }

  return tiles;
}

/******************************************************************************/
bool MoveSkillComponent::IsTileValid(UrsineEngine::GameObject& aBoard,
                                     const TileLocation& aLocation)
{
  bool success = false;

  auto parent = GetParent();
  if(parent != nullptr)
  {
    auto behaviorComp = parent->GetFirstComponentOfType<CharacterBehaviorComponent>();
    if(behaviorComp != nullptr)
    {
      auto movements = behaviorComp->GetMovements(aBoard,
                                                  aLocation);
      auto foundLocation = std::find(movements.begin(),
                                     movements.end(),
                                     aLocation);
      if(foundLocation != movements.end())
      {
        success = true;
      }
    }
  }

  return success;
}

/******************************************************************************/
void MoveSkillComponent::ProtectedSelect()
{
}

/******************************************************************************/
void MoveSkillComponent::ProtectedExecute()
{
}
