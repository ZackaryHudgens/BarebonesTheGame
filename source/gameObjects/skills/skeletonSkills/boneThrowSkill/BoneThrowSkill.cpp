#include "BoneThrowSkill.hpp"

#include <sstream>

#include <SpriteComponent.hpp>

#include "BoardLayoutComponent.hpp"

#include "ProjectileVisualEffectBehaviorComponent.hpp"

using Barebones::BoneThrowSkill;

/******************************************************************************/
BoneThrowSkill::BoneThrowSkill(UrsineEngine::GameObject& aCharacter)
  : SimpleSkill(aCharacter, 2)
{
  SetName("Bone Throw");
  SetDescription("Throw 'em a bone.");
  SetDamage(2);
}

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> BoneThrowSkill::CreateVisualEffect(UrsineEngine::GameObject& aBoard,
                                                                             const TileLocation& aLocation)
{
  std::unique_ptr<UrsineEngine::GameObject> visualEffect = nullptr;

  auto boardLayoutComponent = aBoard.GetFirstComponentOfType<BoardLayoutComponent>();
  if(boardLayoutComponent != nullptr)
  {
    auto targetCharacterObject = boardLayoutComponent->GetCharacterAtLocation(aLocation);
    if(targetCharacterObject != nullptr)
    {
      std::stringstream nameStream;
      nameStream << "boneVisualEffect_" << aLocation.first << "_" << aLocation.second;
      visualEffect = std::make_unique<UrsineEngine::GameObject>(nameStream.str());
      visualEffect->SetScale(glm::vec3(0.7, 0.7, 1.0));

      // Add a projectile behavior component to the visual effect object.
      visualEffect->AddComponent(std::make_unique<ProjectileVisualEffectBehaviorComponent>(targetCharacterObject->GetPosition(), 0.5));

      // Create a sprite and add it to the visual effect object.
      auto spriteComponent = std::make_unique<UrsineEngine::SpriteComponent>();
      spriteComponent->SetRenderOption(GL_DEPTH_TEST, false);

      UrsineEngine::Texture texture;
      texture.CreateTextureFromFile("resources/sprites/skills/bone.png");
      spriteComponent->SetTexture(texture);

      std::string vertexFile = "resources/shaders/TexturedMeshWithFadeShader.vert";
      std::string fragmentFile = "resources/shaders/TexturedMeshWithFadeShader.frag";
      UrsineEngine::Shader shader(vertexFile, fragmentFile);
      spriteComponent->AddShader("default", shader);
      spriteComponent->SetCurrentShader("default");

      visualEffect->AddComponent(std::move(spriteComponent));

      auto characterObject = boardLayoutComponent->GetCharacterAtLocation(GetCharacterLocation(aBoard));
      if(characterObject != nullptr)
      {
        visualEffect->SetPosition(characterObject->GetPosition());
      }
    }
  }

  return std::move(visualEffect);
}
