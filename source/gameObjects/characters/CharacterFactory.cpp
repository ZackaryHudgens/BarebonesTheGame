#include "CharacterFactory.hpp"

#include <SpriteComponent.hpp>

#include "HealthBarMeshComponent.hpp"

#include "BasicHumanBehaviorComponent.hpp"
#include "BasicSkeletonBehaviorComponent.hpp"

#include <iostream>

using Barebones::CharacterFactory;

/******************************************************************************/
std::unique_ptr<UrsineEngine::GameObject> CharacterFactory::CreateCharacter(const CharacterType& aType,
                                                                            const std::string& aName)
{
  auto newCharacter = std::make_unique<UrsineEngine::GameObject>(aName);
  switch(aType)
  {
    case CharacterType::eBASIC_SKELETON:
    {
      newCharacter->AddComponent(std::make_unique<BasicSkeletonBehaviorComponent>());

      // Create and set up the sprite.
      auto newSprite = std::make_unique<UrsineEngine::SpriteComponent>();

      // Set up the shader.
      std::string vertexFile = "resources/shaders/TexturedMeshWithFadeShader.vert";
      std::string fragmentFile = "resources/shaders/TexturedMeshWithFadeShader.frag";
      UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);

      defaultShader.Activate();
      defaultShader.SetFloat("fadeValue", 0.0);
      defaultShader.SetVec4("fadeColor", glm::vec4(0.125, 0.125, 0.125, 1.0));

      newSprite->AddShader("defaultShader", defaultShader);
      newSprite->SetCurrentShader("defaultShader");

      // Set up the spritesheet and animations.
      UrsineEngine::Texture spritesheet;
      spritesheet.CreateTextureFromFile("resources/sprites/skeletons/basicSkeletonSpritesheet.png");
      newSprite->SetTexture(spritesheet);

      newSprite->CreateAnimation("walking");

      UrsineEngine::TextureClip clip;
      clip.mHeight = 16;
      clip.mWidth = 16;
      clip.mX = 0;
      clip.mY = 0;
      newSprite->AddFrameToAnimation("walking", clip);

      clip.mX = 16;
      newSprite->AddFrameToAnimation("walking", clip);

      newSprite->SetAnimation("walking");
      newSprite->SetSpeedOfAnimation(3.0);

      // Finally, add the sprite.
      newCharacter->AddComponent(std::move(newSprite));

      break;
    }
    case CharacterType::eBASIC_HUMAN:
    {
      newCharacter->AddComponent(std::make_unique<BasicHumanBehaviorComponent>());

      // Create and set up the sprite.
      auto newSprite = std::make_unique<UrsineEngine::SpriteComponent>();

      // Set up the shader.
      std::string vertexFile = "resources/shaders/TexturedMeshWithFadeShader.vert";
      std::string fragmentFile = "resources/shaders/TexturedMeshWithFadeShader.frag";
      UrsineEngine::Shader defaultShader(vertexFile, fragmentFile);

      defaultShader.Activate();
      defaultShader.SetFloat("fadeValue", 0.0);
      defaultShader.SetVec4("fadeColor", glm::vec4(0.125, 0.125, 0.125, 1.0));

      newSprite->AddShader("defaultShader", defaultShader);
      newSprite->SetCurrentShader("defaultShader");

      // Set up the spritesheet and animations.
      UrsineEngine::Texture spritesheet;
      spritesheet.CreateTextureFromFile("resources/sprites/enemies/basicHuman.png");
      newSprite->SetTexture(spritesheet);

      // Finally, add the sprite.
      newCharacter->AddComponent(std::move(newSprite));

      break;
    }
    default:
    {
      break;
    }
  }

  // Add a health bar to this character as a child object.
  auto healthBarObject = std::make_unique<UrsineEngine::GameObject>("healthBar");
  auto healthBarMeshComponent = std::make_unique<HealthBarMeshComponent>();

  auto characterBehaviorComponent = newCharacter->GetFirstComponentOfType<CharacterBehaviorComponent>();
  if(characterBehaviorComponent != nullptr)
  {
    healthBarMeshComponent->SetCharacter(*characterBehaviorComponent);
  }

  healthBarObject->AddComponent(std::move(healthBarMeshComponent));

  // Place the health bar above the character sprite.
  auto characterMesh = newCharacter->GetFirstComponentOfType<UrsineEngine::MeshComponent>();
  if(characterMesh != nullptr)
  {
    auto healthBarPos = newCharacter->GetPosition();
    healthBarPos.y += (characterMesh->GetHeight() / 2.0);
    healthBarPos.y += 0.1;
    healthBarObject->SetPosition(healthBarPos);
  }

  newCharacter->AddChild(std::move(healthBarObject));

  return std::move(newCharacter);
}
